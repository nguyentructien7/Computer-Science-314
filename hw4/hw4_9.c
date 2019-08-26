/*-----------------------------------------------------------------//
Author: Tien Nguyen
Date: oct/21/2018
homework 4 number 9
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char ** argv)  {
    //verify we have enough paramater pass
    if(argc!= 2){
        printf("error need an output file" );
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
    fclose(inputFile);
    int fileDescriptor=open(argv[1], O_RDONLY);
    //copy to the memory page
    char* data = mmap(NULL,fileSize,PROT_WRITE,MAP_PRIVATE, fileDescriptor,0);
    
    //outputing the data into the output file in reverse
    FILE* outputFile =fopen(argv[1], "wb+");
    for(int i =0; i<fileSize; i+=sizeof(char)){
        fwrite(&(data[fileSize-i]),sizeof(char),1,outputFile);
    }
}

