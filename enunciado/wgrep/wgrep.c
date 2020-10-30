#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bufferSize 1000

//Function instance
int compare_lines(char *, char *);
int get_number_lines(char *);
void compare_text(char *, FILE *);

//Main function
int main(int argc, char *argv[])
{
    //Validating when the command is executed without parameters
    if (argc == 1)
    {
        printf("wgrep: searchterm [file ...]");
        printf("\n");
        exit(1);
        //Validating when the term is NULL, no comparisions
    }
    else if (strcmp(argv[1], "") == 0 && argc >= 2)
    {
        printf("wgrep: The term is NULL, in this case there isn't any comparisions \n");
        exit(0);
        //Validating to apply the logic when there isn't files added and term isn't null, it should works
    }
    else if (argc == 2 && strcmp(argv[1], "") != 0)
    {
        compare_text(argv[1], stdin);
        //printf("wgrep: This is the case we have to read from Stdin and compare the line - BUILDING \n");
        exit(0);
    }

    //In this case the system is receiving a term no NULL and files to open to make the comparision
    for (int i = 2; i < argc; i++)
    {
        //Validating when there is any problem openning the file
        if (compare_lines(argv[1], argv[i]) != 0)
        {
            printf("wgrep: cannot open file");
            printf("\n");
            exit(1);
        }
    }
    //The command finish to read sucessfully all files
    exit(0);
}

//Function declare - This function will get the lines that has the string required for the user
int compare_lines(char *term, char *file)
{
    //Buffer
    char *lineBuffer = NULL;
    size_t lineBufferSize;
    //the quantity of character that a line has
    size_t lineSize;
    int fileSize;
    FILE *f = fopen(file, "r");
    if (f == NULL)
    {
        //file wasn't able to be open
        return 1;
    }
    else
    {
        //It is required to know how many lines we must compare
        fileSize = get_number_lines(file);
        //First for to move for every line of the file
        for (int i = 0; i < fileSize; i++)
        {
            //We take the line in lineBuffer and the Line character size
            lineSize = getline(&lineBuffer, &lineBufferSize, f);
            //If some of the term is on the lineBuffer the result won't be equal null
            if (strstr(lineBuffer, term) != NULL)
            {
                printf("%s", lineBuffer);
            }
        }
        fclose(f);
        //file was read correctly
        return 0;
    }
}

//Function declare - This function will get the how many lines the file has
int get_number_lines(char *file)
{
    //Buffer
    char temp[50];
    int cont = 0;
    FILE *f = fopen(file, "r");
    while (!feof(f))
    {
        fgets(temp, 50, f);
        cont++;
    }
    fclose(f);
    return cont;
}

void compare_text(char *term, FILE *line)
{
    char listBuffer[bufferSize];
    //The line wrote is read and compare, in case the term exist in the list the sentence is printed
    while (fgets(listBuffer, bufferSize, line) != NULL)
    {
        if (strstr(listBuffer, term) != NULL)
        {
            printf("%s", listBuffer);
        }
    }
}

