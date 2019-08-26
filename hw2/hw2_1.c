/*-----------------------------------------------------------------//
Author: Tien Nguyen
Date: sept/5/2018
homework 2 number 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char** argv){
    FILE *pFile;
    char mystring[1];
    int index;
    int line;
    int word;
    char* filename;
    int totalWord =0;
    int totalLine =0;
    int totalInteger =0;
    
    //looping over the files
    for(int i=1; i<argc;i++){
        filename=argv[i];
        line=1;
        word=1;
        index=0;
        pFile =fopen(filename, "r");
        
        if (pFile ==NULL)
            perror ("Error opening File");
        else{
            //while there is something left to read increase index value
            while(fread(mystring,1,1,pFile) == 1){
                index++;
                //comparing string
                if(mystring[0] == '\n' || mystring[0] == '\r')
                    line++;
                if(isspace(mystring[0]))
                    word++;
            }
            printf("\t%d\t%d\t%d\t%s\n", line, word, index*(int)sizeof(char),filename);
            fclose(pFile);
            //calculate the total
            totalWord += word;
            totalLine += line;
            totalInteger += index;
            }
    }
    //if we only had one file dont show total
    if (argc>2)
        printf("\t%d\t%d\t%d\ttotal\n", totalWord, totalLine, totalInteger*(int)sizeof(char));
    //check if we passed any file then we end now
    if (argc>1)
        return 0;
    
    //read text typed into terminal
    line=0;
    word=1;
    index=0;
    //reading each charactor in the console
    while(fread(mystring,1,1,stdin) == 1){
        index++;
        //comparing string
        if(mystring[0] == '\n' || mystring[0] == '\r'){
            line++;
            break;
        }
        //checking through spaces
        if(isspace(mystring[0]))
            word++;
    }
    printf("    %d  %d  %d  \n", line, word, index*(int)sizeof(char));
    return 0;
}
