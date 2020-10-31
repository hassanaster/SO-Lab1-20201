#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function instance
int comprese_lines(char *);

//Main function
int main(int argc, char *argv[])
{
    //Validating when the command is executed without parameters

    if (argc == 1)
    {
        printf("wzip: file1 [file2 ...]");
        printf("\n");
        exit(1);
        //Validating when the term is NULL, no comparisions
    }
    //comprese will be displaying by stdout
    /* else if (argc == 2)
    {
        //compare_text(argv[1], stdin);
        //printf("wgrep: This is the case we have to read from Stdin and compare the line - BUILDING \n");
        exit(0);
    } // in this case whwn argc == 2 I have to validate if I have or not file to write the result or no: Case 1 write in the file added, Case 2: write with stout*/
    //Open question - how to open the file to write after greater than ?

    //In this case the system is receiving all the files to comprese in just one file wich is received
    for (int i = 1; i < argc; i++)
    {
        //Validating when there is any problem openning the file
        //printf("Entro al for \n");
        //printf("%s \n", argv[i]);
        if (comprese_lines(argv[i]) != 0)
        {
            printf("wzip: cannot open file");
            printf("\n");
            exit(1);
        }
    }
    //The command finish to read sucessfully all files
    exit(0);
}

//Function declare - This function will get the lines that has the string required for the user
int comprese_lines(char *file)
{
    //printf("Entro a copmprese_line function \n");
    //int fileSize;
    FILE *f = fopen(file, "r");
    char next, actual = '\0';
    int cont = 0;
    if (f == NULL)
    {
        //file wasn't able to be open
        return 1;
    }
    else
    {   
        actual = getc(f);
        while (!feof(f))
        {   next = getc(f);
            if (next==actual)
            {
                cont++;
            }
            else
            {   
                printf("%d%c", cont + 1, actual);
                actual = next;
                //just in the case we have a repetitive string we set the counter to 0. If there is just 1 of a character, we don't need to set the counter in 0.
                if (cont>0)
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

