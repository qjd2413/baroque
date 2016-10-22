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
    for(size_t ii = 0; ii < linecount; ii++) {
        printf("%zu %s\n", ii, lines[ii]);
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
        length = strlen(buf);
        buf[length-1] = 0;
        strtok(buf, "#");
        if(!(length = strlen(buf))) {
            continue;
        }
        lines[linecount] = (char*)malloc(length * sizeof(char) + 1);
        strcpy(lines[linecount], buf);
        linecount++;
        printf("%s\n", buf);
    }
    fclose(fp);
    free(buf);
    return linecount;
}
