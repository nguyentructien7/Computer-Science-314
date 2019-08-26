/*-----------------------------------------------------------------//
Author: Tien Nguyen
Date: Oct/21/2018
homework 4 number 8
*/

#include <stdio.h>
#include <stdlib.h>



int main(int argc, char ** argv)  {
    //verify we have enough paramater pass
    if(argc!= 3){
        printf("error need an input file or output file" );
        exit(1);
    }
    //open the inputfile
    FILE* inputFile = fopen(argv[1],"rb");
    if( inputFile==NULL){
        printf("File does not exit");
        exit(1);
    }
    //finding the file size
    fseek (inputFile,0,SEEK_END);
    int fileSize = ftell(inputFile);
    fseek (inputFile,0,SEEK_SET);
    //copying the data into memory
    char data[fileSize];
    for(int i =0; i<fileSize; i+=sizeof(char)){
        fread(&(data[i]),sizeof(char),1,inputFile);
    }
    //outputing the data into the output file in reverse
    FILE* outputFile =fopen(argv[2], "wb+");
    for(int i =0; i<fileSize; i+=sizeof(char)){
        fwrite(&(data[fileSize-i]),sizeof(char),1,outputFile);
    }
}
