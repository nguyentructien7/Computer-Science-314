/*------------------------------------//
Problem 2 for CS 314 Operating Systems
//------------------------------------*/
	//====// Includes
		#include <math.h>
		#include <stdlib.h>
		#include <stdio.h>
		#include <string.h>
		#include <sys/types.h>
		#include <dirent.h>
		#include <sys/stat.h>

	//====// Defines
		#define MAX_FILENAME_LENGTH 50

	//====// Structs
		//Prototype for bin structs
		struct Bin; //Stores a pointer to its data and a pointer to next bin
		struct BinData; //Stores data for each entry in the bin and a pointer to next entry
		//Definition and typedef for structs
		typedef struct BinData{
			char name[MAX_FILENAME_LENGTH];
			int size;
			struct BinData* next;
		} BinData;
		typedef struct Bin{
			BinData* data;
			struct Bin* next;
		} Bin;

	//====// Functions
		void PrintBins(Bin* binRoot, int binSize){
			Bin* bin = binRoot;
			BinData* data;
			int i = 1; //bin index

			//look at each bin
			while(bin != NULL){
				printf("Bin %d, size %d - %d bytes\n", i, (i-1)*binSize, i*binSize-1);
				//look at each entry in bin
				data = bin->data;
				int j = 1; //bin entry index
				while(data != NULL){
					printf("\t%d: %s: %d bytes\n", j, data->name, data->size);
					data = data->next;
					j++;
				}
				bin = bin->next;
				i++;
			}
		}

		//prototype for search
		int Search(char* rootPath, Bin* binRoot, int binSize);
		//Definition for search function
		//Recursively searches passed directory
		int Search(char* rootPath, Bin* binRoot, int binSize){
			struct dirent* dent;
			DIR* dir = opendir(rootPath);

		    if (dir == NULL){
		        printf("Could not open source directory\n");
		        return -1;
		    }

		    //read each sub file or directory
		    while ((dent = readdir(dir)) != NULL){
		        struct stat st;
		        char path[MAX_FILENAME_LENGTH];
		        int size;

		        //skip entries for self and parent
		        if (strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0)
		            continue;

		        //create path
		        strcpy(path, rootPath);
		        strcpy(path+strlen(path), "/");
		        strcpy(path+strlen(path), dent->d_name);

		        //Read file stats
		        if (stat(path, &st) < 0){
		            printf("Could not read from %s\n", path);
		            continue;
		        }

		        //check if a directory if so recurse
		        if (S_ISDIR(st.st_mode)) 
		        	Search(path, binRoot, binSize);

		        //record file size
		        size = st.st_size;

		        //find space in bin
		        int binNum = floor(size / (binSize+0.0));
		        Bin* bin = binRoot;

		       	//go to binNum
		       	for (int i = 0; i < binNum; i++){
		       		//check if next bin is valid, if not make it
		       		if (bin->next == NULL){
		       			Bin* newbin;
		       			newbin = malloc(sizeof(Bin));
		       			newbin->next = NULL;
		       			newbin->data = NULL;
		       			bin->next = newbin;
		       		}
		       		//grab next bin
		       		bin = bin->next;
		       	}
		       	//create BinData
		       	BinData* data;
		       	data = malloc(sizeof(BinData));
		       	strcpy(data->name, path);
		       	data->size = size;
		       	data->next = bin->data;
		       	//insert into bin
		       	bin->data = data;
		    }
		    closedir(dir);

		    return 0;
		}

		//Main entry point for program execution
		int main (int argc, char** argv){
			//Check command line parameters
			if (argc != 3){
				printf("Unexepected number of parameters given (expected 2 got %d)\n", argc-1);
				printf("Correct usage: ProgramName RelativeDirectory BinSize\n");
				return -1;
			}

			//setup variables
			char* rootDir = argv[1];
			int binSize = atoi(argv[2]);
			Bin* binRoot;

			//setup bin
			binRoot = malloc(sizeof(Bin));
			binRoot->next = NULL;
			binRoot->data = NULL;

			//search directories recursively
			if (Search(rootDir, binRoot, binSize) < 0)
				return -1; //exit early if error occurred

			PrintBins(binRoot, binSize);

			return 0;
		}