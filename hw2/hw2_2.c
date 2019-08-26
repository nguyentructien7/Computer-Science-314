/*-----------------------------------------------------------------//
Author: Tien Nguyen
Date: sept/5/2018
homework 2 number 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char** argv){
    FILE *pFile;
    char mystring[1];
    int line;
    int bflag = 0;
    char* filename;
    
    //looping over the files
    for(int i=1; i<argc;i++){
        filename=argv[i];
        line=1;

        if (strcmp(filename, "-b") == 0){
            bflag = 1;
            continue;
        }
        if (bflag == 1)
            printf("\t%d\t", line);
        
        pFile =fopen(filename, "r");
        
        if (pFile ==NULL)
            perror ("Error opening File");
        else{
            //read character by character
            while(fread(mystring,1,1,pFile) == 1){
                printf("%c", mystring[0]);
                //comparing string
                if((mystring[0] == '\n' || mystring[0] == '\r') && bflag == 1){
                    line++;
                    printf("\t%d\t", line);
                }
            }
        fclose(pFile);
        printf("\n");
        }
    }
    if ((argc>1 && bflag == 0) || (argc>2 && bflag == 1))
        return 0;
    
    //read directly from stdin
    line = 0;
    int showline = 1;
    //reading every character
    while (fread(mystring,1,1,stdin) == 1){
        if (bflag == 1 && showline == 1){
            line++;
            printf("\t%d\t", line);
            showline = 0;
        }
        //print the next character
        printf("%c", mystring[0]);
        if (mystring[0] == '\n' || mystring[0] == '\r')
            showline = 1;
    }
    
    return 0;
}
