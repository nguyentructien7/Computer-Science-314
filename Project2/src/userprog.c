#include "lab2-api.h"

typedef struct DB {
  sem_t oSem, nSem, o2Sem;
} DB;

main (int argc, char *argv[])
{
  int nitrogenCount,oxygenCount, i;
  DB *db;
  uint32 handle;
  sem_t spage, oxySem, nitSem, oxy2Sem;
  char handle_str[10], spage_str[10];
  
  switch(argc)
    {//always 1 extra argument we dont care
    case 3:
      nitrogenCount= dstrtol(argv[2],NULL,10);
      oxygenCount = dstrtol(argv[1], NULL, 10);
      break;
    default:
      Printf("Usage: ");
      Printf(argv[0]);
      Printf(" number number\n");
      exit();
  }

  handle = shmget();	//Get a shared memory page
  db = (DB *)shmat(handle);
  if(db==NULL)
  {
    Printf("Could not map the shared page to virtual address, exiting..\n");
    exit();
  }
  //saving it in the share memory page
  oxySem = sem_create(0);
  nitSem = sem_create(0);
  oxy2Sem = sem_create(0);
  db->oSem = oxySem;
  db->nSem = nitSem;
  db->o2Sem = oxy2Sem;
  spage = sem_create(0);	//Get a semaphore to wait till this memory
 	 			//page is mapped to some other process's
				//virtual address space

  ditoa(handle, handle_str);	//Convert the shared page handle to a string
  ditoa(spage, spage_str);	//Convert the semaphore spage to a string
  
  //making oxgygen
  for(i=0; i<oxygenCount; i++){
    char typeString[10];
    ditoa(0, typeString);
    process_create("userprog2.dlx.obj", handle_str, spage_str, typeString, NULL);
  }
  for(i=0; i<nitrogenCount; i++){
    char typeString[10];
    ditoa(1, typeString);
    process_create("userprog2.dlx.obj", handle_str, spage_str, typeString, NULL);
  }
  //making 02 process
  for(i=0; i<oxygenCount/2; i++){
    char typeString[10];
    ditoa(2, typeString);
    process_create("userprog2.dlx.obj", handle_str, spage_str, typeString, NULL);
  }
  for(i=0; i<nitrogenCount; i++){
    char typeString[10];
    ditoa(3, typeString);
    process_create("userprog2.dlx.obj", handle_str, spage_str, typeString, NULL);
  }
  sem_wait(spage);		//Wait till at least one process grabs the
  				//shared memory page. Otherwise the page could
				//be released before anyone grabs it!
}
