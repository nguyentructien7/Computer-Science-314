/*-----------------------------------------------------------------//
Author: Tien Nguyen
Date: oct/21/2018
homework 4 number 10
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/time.h>
#include <unistd.h>
#include <assert.h>

long nanosec(struct timeval t){
    return((t.tv_sec*1000000+t.tv_usec)*1000);
}



int main(int argc, char ** argv)  {
    //verify we have enough paramater pass
    if(argc!= 2){
        printf("error need an output file" );
        exit(1);
    }
    int res;
    struct timeval t1, t2;
    res=gettimeofday(&t1,NULL); assert(res==0);
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
    res=gettimeofday(&t2,NULL);   assert(res==0);
    printf("executing time is: %ld\n",nanosec(t2)-nanosec(t1));
}

