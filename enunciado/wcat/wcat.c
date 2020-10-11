#include <stdio.h>
#include <stdlib.h>

#define bufferSize 40

//Function instance
int get_files(char *);

//Main function
int main(int argc, char *argv[]){
    for(int i=1; i< argc; i++){
        if(get_files(argv[i])!=0){
            //when this happends, the file wasn't able to be open
            printf("This command isn't able to open the file\n");
            exit(-1); 
        }
    }
    //The command finish to read sucessfully all files
    exit(0);
}

//Function declare
int get_files(char *file){
    //Buffer
    char listBuffer[bufferSize];
    FILE *app= fopen(file, "r");
    if(app == NULL){
        //file wasn't able to be open
        return 1;
    }else {
        while(fgets(listBuffer, bufferSize, app)!=NULL){
            printf("%s", listBuffer);
        }
        fclose(app);
        printf("\n");
        //file was reade correctly
        return 0;
    }
}
