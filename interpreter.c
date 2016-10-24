#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Usage: ./a.out filename\n");
        return 1;
    }
    char** lines = (char**)calloc(1024, sizeof(char*));
    size_t linecount = preprocess(argv[1], lines);
    if(!linecount) {
        printf("Error: file does not exist or is empty\n");
        return 1;
    }
    lines = (char**)realloc(lines, linecount * sizeof(char*));
    int key = extractKey(lines, linecount);
    if(key == -1) {
        printf("Error: failed to detect key\n");
        return 1;
    }
    printf("Key detected: %c\n", key + 65);
    for(size_t ii = 0; ii < linecount; ii++) {
        free(lines[ii]);
    }
    free(lines);
}

size_t preprocess(char* filename, char** lines) {
    FILE *fp;
    fp=fopen(filename, "r");
    if(!fp) {
        return 0;
    }
    size_t bufsize = 1024;
    char* buf = (char*)malloc(bufsize * sizeof(char));
    size_t length;
    size_t linecount = 0;
    while(fgets(buf, bufsize, fp)) {
        if(buf[0] == '!' && buf[1] == '!') {
            continue;
        }
        length = strlen(buf);
        buf[length-1] = 0; //remove newline from end
        if(!(length = strlen(buf))) {
            continue;
        }
        lines[linecount] = (char*)malloc(length * sizeof(char) + 1);
        strcpy(lines[linecount], buf);
        linecount++;
    }
    fclose(fp);
    free(buf);
    return linecount;
}

int extractKey(char** lines, size_t linecount) {
    int potentialKey = -1;
    for(size_t ii = 0; ii < linecount; ii++) {
        if(lines[ii][0] == '*' && lines[ii][1] == 'k' && lines[ii][2] == '[') {
            size_t end = strcspn(lines[ii], "]");
            size_t sharps = 0, flats = 0;
            for(size_t jj = 3; jj < end; jj++) {
                if(lines[ii][jj] == '#') {
                    sharps++;
                }
                if(lines[ii][jj] == '-') {
                    flats++;
                }
            }
            if(sharps && flats) {
                return -1;
            }
            if(sharps) {
                return keyFromSharpCount(sharps);
            }
            return keyFromFlatCount(flats);
        }
        if(potentialKey == -1 && lines[ii][0] == '*' && lines[ii][2] == ':') {
            potentialKey = charToNote(lines[ii][1]);
        }
    }
    return potentialKey;
}

int charToNote(char ch) {
    if(ch >= 65 && ch <= 71) {
        return ch - 65;
    }
    if(ch >= 97 && ch <= 103) {
        return ch - 97;
    }
    return -1;
}

int keyFromSharpCount(size_t sharpcount) {
    int sharps[] = {2, 6, 3, 0, 4, 1, 5};
    return sharps[sharpcount % 8];
}
int keyFromFlatCount(size_t flatcount) {
    int flats[] = {2, 5, 1, 4, 0, 3, 6};
    return flats[flatcount % 8];
}
