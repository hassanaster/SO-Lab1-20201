#include <stdio.h>
#include <stdlib.h>

//Function instance
int compare_lines(char *, char *);
int get_number_lines(char *);

//Main function
int main(int argc, char *argv[]){

    //Validating when the command is executed without parameters
    if (argc==0){
        printf("wgrep: searchterm [file...] \n");
        exit(1);
    //Validating when the term is NULL, no comparisions 
    }else if(strcmp(argv[1], "NULL")==0 && argc>=1){
        printf("wgrep: The term is NULL, in this case there isn't any comparisions \n");
        exit(0); 
    //Validating to apply the logic when there isn't files added and term isn't null, it should works
    } else if(argc==1 && strcmp(argv[1], "NULL")!=0){
        printf("wgrep: This is the case we have to read from Stdin and compare the line - BUILDING \n");
        //We have to create the logic to receive all entries and compare with the term, exit when user clic some key
        exit(0); 
    }

    //In this case the system is receiving a term no NULL and files to open to make the comparision
    for(int i=2; i< argc; i++){
        //Validating when there is any problem openning the file
        if(compare_lines(argv[1], argv[i])!=0){
            printf("wgrep: cannot open file \n");
            exit(1); 
        }
    }
    //The command finish to read sucessfully all files
    exit(0);
}

//Function declare - This function will get the lines that has the string required for the user
int compare_lines(char *term, char *file){
    //Buffer
    char *lineBuffer = NULL;
    size_t lineBufferSize;
    //the quantity of character that a line has
    size_t lineSize; 
    int fileSize;
    int termSize;
    FILE *f= fopen(file, "r");
    if(f == NULL){
        //file wasn't able to be open
        return 1;
    }else {
        //It is required to know what is the size from the term to compare
        termSize = strlen(term);
        //Create a char with the size of the term to compare with the term
        char tempBuffer[termSize];
        //It is required to know how many lines we must compare
        fileSize = get_number_lines(f);
        //First for to move for every line of the file
        for(int i=0; i<fileSize; i++){
            //We take the line in lineBuffer and the Line character size
            lineSize = getline(&lineBuffer, &lineBufferSize, f);
            //This for is to move in the lineBuffer got
            for(int j=0; j<lineSize; j++){
                //This for is to get the quantity of characters to compare with term from the right position in the line Buffer
                for(k=j;k<termSize+j;k++){
                    strcpy(tempBuffer, lineBuffer[k]);
                }
                //If the piece of lineBuffer we got in the step before is the same of term we print the bufferLine and we out from the cycle of the line to keep comparing the rest lines of the file
                if(strcmp(tempBuffer,term)==0){
                    printf("%s", lineBuffer);
                    printf("\n");
                    j=lineSize;
                }
                //It is needded to make empty this buffer to be able to compare with a new piece from lineBuffer
                tempBuffer = NULL;
            }
        }
        fclose(f);
        printf("\n");
        //file was ready correctly
        return 0;
    }
}

//Function declare - This function will get the how many lines the file has
int get_number_lines(char *file){
    //Buffer
    char temp[50];
    int cont = 0;
    FILE *f= fopen(file, "r");
    while(!feof(f)){
        fgets(temp,50,f);
        cont++;
    }
    fclose(f);
    return cont;
}

