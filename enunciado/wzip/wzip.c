#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function instance
int comprese_lines_file(char *, char *);
int comprese_lines_stdout(char *, FILE *);
void convert(int counter, char character, FILE *writeFile);

#define COUTERLENGHT  4
#define CHARACTERLENGHT 1

//Main function
int main(int argc, char *argv[])
{
    //Boolean to validate if there is or not a file in the command: '1' there isn't, '0' it is a file
    int isFile = 1;
    char *file;

    //Validating when the command is executed without parameters
    if (argc == 1)
    {
        printf("wzip: file1 [file2 ...]");
        printf("\n");
        exit(1);
    }

    //Validating if we have a file to write the comprese or not and saving the name of the file
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], ">") == 0)
        {
            isFile = 0;
            i++;
            file = argv[i];
        }
    }

    //If we have a file we activate the function to write in a file
    if (isFile == 0)
    {
        for (int i = 1; i < argc; i++)
        {
            //Validating when there is any problem openning the file
            if (comprese_lines_file(argv[i], file) != 0)
            {
                printf("wzip: cannot open file");
                printf("\n");
                exit(1);
            }
        }
    }
    //If we don't have a file we activate the output for stdout
    else
    {
        for (int i = 1; i < argc; i++)
        {
            //Validating when there is any problem openning the file
            if (comprese_lines_stdout(argv[i], stdout) != 0)
            {
                printf("wzip: cannot open file");
                printf("\n");
                exit(1);
            }
        }
    }
    //The command finish to read sucessfully all files
    exit(0);
}

//Function declare - This function will compress the lines from a file to write in other file received
int comprese_lines_file(char *readFile, char *writeFile)
{
    FILE *f = fopen(readFile, "r");
    //'a' format to write at the end of the file
    FILE *fw = fopen(readFile, "a");
    char next, actual = '\0';
    int cont = 0;
    if (f == NULL)
    {
        //file wasn't able to be open
        return 1;
    }
    else
    {   //In this case the file is open, and we start to get each character for each file
        actual = getc(f);
        while (!feof(f))
        {   //I get the next character to compare actual and next
            next = getc(f);
            if (next == actual)
            {
                cont++;
            }
            else
            {
                convert(cont+1, actual, fw);
                actual = next;
                //just in the case we have a repetitive string we set the counter to 0. If there is just 1 of a character, we don't need to set the counter in 0.
                if (cont > 0)
                {
                    cont = 0;
                }
            }
        }
        fclose(f);
        fclose(fw);
        //file was read correctly
        return 0;
    }
}

//Function declare - This function will compress the lines from a file to write stdout file
int comprese_lines_stdout(char *readFile, FILE *writeFile){
    FILE *f = fopen(readFile, "r");
    char next, actual = '\0';
    int cont = 0;
    if (f == NULL)
    {
        //file wasn't able to be open
        return 1;
    }
    else
    {   //In this case the file is open, and we start to get each character for each file
        actual = getc(f);
        while (!feof(f))
        {   //I get the next character to compare actual and next
            next = getc(f);
            if (next == actual)
            {
                cont++;
            }
            else
            {
                convert(cont+1, actual, writeFile);
                actual = next;
                //just in the case we have a repetitive string we set the counter to 0. If there is just 1 of a character, we don't need to set the counter in 0.
                if (cont > 0)
                {
                    cont = 0;
                }
            }
        }
        fclose(f);
        //file was read correctly
        return 0;
    }
}

//Method that converts the character counter in bytes and the character in ASCII
void convert(int counter, char character, FILE *writeFile)
{
    fwrite(&counter, COUTERLENGHT, 1, writeFile);
    fwrite(&character, CHARACTERLENGHT, 1, writeFile);
}
//Structure fwrite: OFFSET (memory address), length of the data, length or unit size, file handle.