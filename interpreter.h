
int main(int argc, char* argv[]);

size_t preprocess(char* filename, char** lines);

int extractKey(char** lines, size_t linecount);

int charToNote(char ch);

int keyFromSharpCount(size_t sharpcount);

int keyFromFlatCount(size_t flatcount);
