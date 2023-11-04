#include <stdio.h>
#include <string.h>

FILE *fptr;
char filename[] = "";

void printHelp();
int returnSizeInBytes(char filename[]);
int returnLinesInFile(char filename[]);

int main(int argc, char const *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        if(strchr(argv[i], '-') == NULL ) {
            // Copy filename to variable
            strcpy(filename, argv[i]);
        }
    }

    for (int i = 1; i < argc; ++i)
    {
        if(strstr(argv[i], "-c") != NULL ) {
            returnSizeInBytes(filename);
        } 
        else if(strstr(argv[i], "-h") != NULL ) {
            printHelp();
        }
        else if(strstr(argv[i], "-l") != NULL ) {
            returnLinesInFile(filename);
        }
    }

    return 0;
    
}

void printHelp() {
    printf(""
    "Usage: awc [OPTION]... [FILE]...\n"
    "Print newline, word, and byte counts for each FILE, and a total line if\n"
    "more than one FILE is specified.  A word is a non-zero-length sequence of\n"
    "characters delimited by white space.\n\n"

    "With no FILE, or when FILE is -, read standard input.\n\n"

    "The options below may be used to select which counts are printed, always in\n"
    "the following order: newline, word, character, byte, maximum line length.\n"
    "-c, --bytes            print the byte counts\n"
    "");
}

int returnSizeInBytes(char filename[]) {
    fptr = fopen(filename, "r");

    if(fptr == NULL){
        printf("File not found!\n");
        return -1;
    }

    fseek(fptr,0,SEEK_END);
    printf("%ld %s\n", ftell(fptr), filename);

    fclose(fptr);
    
    return 0;
}

int returnLinesInFile(char filename[]) {

    int newline_count = 0;

    fptr = fopen(filename, "r");

    if(fptr == NULL){
        printf("File not found!\n");
        return -1;
    }

    for(char c = getc(fptr); c != EOF; c = getc(fptr)) {
        if (c == '\n') {
           newline_count = newline_count + 1;
        }
    }

    fclose(fptr);

    printf("%d %s\n", newline_count, filename);

    return 0;
}
