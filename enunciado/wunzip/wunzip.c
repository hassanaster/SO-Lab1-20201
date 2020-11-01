#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function instance
int decompress_lines_file(char *);

#define COUTERLENGHT 4
#define CHARACTERLENGHT 1

//Main function
int main(int argc, char *argv[])
{
    //Validating when the command is executed without parameters
    if (argc == 1)
    {
        printf("wunzip: file1 [file2 ...]");
        printf("\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++)
    {
        if (decompress_lines_file(argv[i]) != 0)
        {
            printf("wunzip: cannot open file");
            printf("\n");
            exit(1);
        }
    }

    //The command finish to read sucessfully all files
    exit(0);
}

//Function declare - This function will descompress the lines for the file and write in console
int decompress_lines_file(char *readFile)
{
    FILE *f = fopen(readFile, "r");
    char string;
    int cont = 0;
    if (f == NULL)
    {
        //file wasn't able to be open
        return 1;
    }
    else
    { //In this case the file is open, and we start to get the counter and char to write it
        while (!feof(f))
        { //I get the next character to compare actual and next
            fread(&cont, COUTERLENGHT, 1, f);
            fread(&string, CHARACTERLENGHT, 1, f);
            while(cont>0){
                printf("%c", string);
                cont--;
            }
        }
        fclose(f);
        //file was read correctly
        return 0;
    }
}
