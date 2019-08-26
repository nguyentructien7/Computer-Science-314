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
		#define BLOCK_SIZE 1024
		#define MAX_FILENAME_LENGTH 50

	//====// Structs
		//Block struct
		struct Block; 
		typedef struct Block{
			char data[BLOCK_SIZE];
			struct Block* next;
		} Block;
		//File struct
		struct File;
		typedef struct File{
			char name[MAX_FILENAME_LENGTH];
			Block* blocks;
			struct File* next;
		} File;
		//Archive struct
		typedef struct Archive{
			File* files;
		} Archive;

	//====// Functions
		//Opens the passed archive path
		Archive* ArchiveOpen(char* archivePath){
			Archive* archive = malloc(sizeof(Archive));

			//attempt to open archive file
			FILE *infile = fopen(archivePath, "r");
			if (infile == NULL){ 
		        //Archive does not exist make new archive
		        archive->files = NULL;
		    }else{
		    	//Archive exists
		    	fread(archive, sizeof(Archive), 1, infile);

		    	//check if there are files
		    	if(archive->files != NULL){
		    		File* file = malloc(sizeof(File));
		    		fread(file, sizeof(File), 1, infile);
		    		archive->files = file;

		    		//if there is data
		    		if(file->blocks != NULL){
		    			Block* block = malloc(sizeof(Block));
		    			fread(block, sizeof(Block), 1, infile);
		    			file->blocks = block;

		    			//read in each block
		    			while(block->next != NULL){
		    				Block* newblock = malloc(sizeof(Block));
		    				fread(newblock, sizeof(Block), 1, infile);
		    				block->next = newblock;
		    				block = newblock;
		    			}
		    		}

		    		//read in each file
		    		while(file->next != NULL){
		    			File* newfile = malloc(sizeof(File));
		    			fread(newfile, sizeof(File), 1, infile);
		    			file->next = newfile;
		    			file = newfile;

		    			//if there is data
			    		if(file->blocks != NULL){
			    			Block* block = malloc(sizeof(Block));
			    			fread(block, sizeof(Block), 1, infile);
			    			file->blocks = block;

			    			//read in each block
			    			while(block->next != NULL){
			    				Block* newblock = malloc(sizeof(Block));
			    				fread(newblock, sizeof(Block), 1, infile);
			    				block->next = newblock;
			    				block = newblock;
			    			}
			    		}
		    		}
		    	}
		    }
		    fclose (infile);

		    return archive;
		}

		//Saves the archive
		void ArchiveSave(char* archivePath, Archive* archive){
			//create file to write to
			FILE *outfile = fopen(archivePath, "w");
			if (outfile == NULL) { 
		        fprintf(stderr, "\nError saving archive\n"); 
		        exit (1); 
		    }
		    //write archive struct as header
		    fwrite(archive, sizeof(Archive), 1, outfile);

		    //write files
		    File* file = archive->files;
		    while(file != NULL){
		    	fwrite(file, sizeof(File), 1, outfile);

		    	Block* block = file->blocks;

		    	//write contents of each file block by block
		    	while(block != NULL){
		    		fwrite(block, sizeof(Block), 1, outfile);
		    		block = block->next;
		    	}

		    	file = file->next;
		    }

		    fclose(outfile);
		}

		//Add a file to the archive
		void ArchiveAdd(char* archivePath, char* filePath){
			Archive* archive;
			archive = ArchiveOpen(archivePath);

			//Initialize file
			File* file = malloc(sizeof(File));
			file->next = NULL;
			for (int i = 0; i < MAX_FILENAME_LENGTH; i++)
				file->name[i] = '\0';
			strcpy(file->name, filePath);
			Block* block = malloc(sizeof(Block));
			for (int i = 0; i < BLOCK_SIZE; i++)
				block->data[i] = '\0';
			block->next = NULL;
			file->blocks = block;
			file->next = archive->files;
		    archive->files = file;

			//open file we are adding to archive
			FILE *infile = fopen(filePath, "r");
			if (infile != NULL) {
			    //Go to the end of the file
			    if (fseek(infile, 0L, SEEK_END) == 0) {
			        //Get the size of the file.
			        long bufsize = ftell(infile);
			        if (bufsize == -1) { /* Error */ }

			        //Allocate our buffer to that size.
			        char* source = malloc(sizeof(char) * (bufsize + 1));

			        //Go back to the start of the file.
			        if (fseek(infile, 0L, SEEK_SET) != 0) { /* Error */ }

			        //Read the entire file into memory.
			        size_t newLen = fread(source, sizeof(char), bufsize, infile);
			        if (ferror( infile ) != 0 ) {
			            fputs("Error reading file", stderr);
			        }else{
			            source[newLen++] = '\0';
			        }
			        //now copy this memory buffer into blocks
			        int j = 0;
		    		for(int i = 0; i < bufsize; i++){
		    			//check if block is full
		    			if (j == BLOCK_SIZE){
		    				//go to next block
		    				j = 0;
		    				Block* newblock = malloc(sizeof(Block));
		    				for (int i = 0; i < BLOCK_SIZE; i++)
								newblock->data[i] = '\0';
		    				block->next = newblock;
		    				newblock->next = NULL;
		    				block = newblock;
		    			}
		    			//copy data into block
		    			block->data[j] = source[i];
		    			j++;
		    		}

					free(source);
			    }
		    	fclose(infile);
			}

			ArchiveSave(archivePath, archive);
		}

		//List all files in archive
		void ArchiveList(char* archivePath){
			Archive* archive;
			archive = ArchiveOpen(archivePath);

			printf("Contents of:\t%s\n", archivePath);

			//look at each file
			File* file = archive->files;
			while(file != NULL){
				printf("\t%s\n", file->name);
				file = file->next;
			}

			ArchiveSave(archivePath, archive);
		}

		//Extract a file from the archive
		void ArchiveExtract(char* archivePath, char* filePath){
			Archive* archive;
			archive = ArchiveOpen(archivePath);

			//open/create file to extract to
			FILE *outfile = fopen(filePath, "w");
			if (outfile == NULL) { 
		        fprintf(stderr, "\nError extracting file\n"); 
		        exit (1); 
		    }

		    //grab file data
		    File* file = archive->files;
		    while(strcmp(file->name, filePath) != 0){
		    	//check if we found the file
		    	if (file == NULL){
		    		fprintf(stderr, "\nFile does not exist in archive\n"); 
		        	exit (1); 
		    	}
		    	file = file->next;
		    }
		    Block* block = file->blocks;

		    //write file data
		    while(block != NULL){
		    	fwrite(block, sizeof(Block), 1, outfile);
		    	block = block->next;
		    }

			ArchiveSave(archivePath, archive);
		}

		//Main entry point for program execution
		int main (int argc, char** argv){
			//Check command line parameters
			if (argc < 2){
				printf("No parameters given, available flags:\n-a archive file\t\tAdds file to archive\n-l archive\t\tLists the files in the archive\n-e archive file\t\tExtracts file from archive\n");
				return -1;
			}

			//Switch based on first parameter
			switch(argv[1][0]){
				case '-':{
					switch(argv[1][1]){
						case 'a':{
							if (argc != 4){
								printf("Unexepected number of parameters given (expected 3 got %d)\n", argc-1);
								printf("Correct usage: ProgramName -a archive FileToAdd\n");
								return -1;
							}
							//grab rest of parameters
							char archive[MAX_FILENAME_LENGTH];
							char file[MAX_FILENAME_LENGTH];
							strcpy(archive, argv[2]);
							strcpy(file, argv[3]);
							ArchiveAdd(archive, file);
							break;
						}
						case 'l':{
							if (argc != 3){
								printf("Unexepected number of parameters given (expected 2 got %d)\n", argc-1);
								printf("Correct usage: ProgramName -l archive\n");
								return -1;
							}
							//grab rest of parameters
							char archive[MAX_FILENAME_LENGTH];
							strcpy(archive, argv[2]);
							ArchiveList(archive);
							break;
						}
						case 'e':{
							if (argc != 4){
								printf("Unexepected number of parameters given (expected 3 got %d)\n", argc-1);
								printf("Correct usage: ProgramName -e archive FileToExtract\n");
								return -1;
							}
							//grab rest of parameters
							char archive[MAX_FILENAME_LENGTH];
							char file[MAX_FILENAME_LENGTH];
							strcpy(archive, argv[2]);
							strcpy(file, argv[3]);
							ArchiveExtract(archive, file);
							break;
						}
						default:{
							printf("Invalid parameter, available flags:\n-a archive file\t\tAdds file to archive\n-l archive\t\tLists the files in the archive\n-e archive file\t\tExtracts file from archive\n");
							return -1;
						}
					}
					break;
				}
				default:{
					printf("Invalid parameter, available flags:\n-a archive file\t\tAdds file to archive\n-l archive\t\tLists the files in the archive\n-e archive file\t\tExtracts file from archive\n");
					return -1;
				}
			}

			return 0;
		}