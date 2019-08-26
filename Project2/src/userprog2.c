#include "lab2-api.h"

typedef struct DB {
  sem_t oSem, nSem, o2Sem;
} DB;

DB* db;

void oReady(){
  Printf("An atom of Oxygen was created\n");
  sem_signal(db->oSem);
}

void nReady(){
  Printf("An atom of Nitrogen was created\n");
  sem_signal(db->nSem);
}

void makeOxygen(){
  sem_wait(db->oSem);
  sem_wait(db->oSem);
  Printf("An atom of O2 was created\n");
  sem_signal(db->o2Sem);
}

void makeNO2(){
  sem_wait(db->o2Sem);
  sem_wait(db->nSem);
  Printf("An atom of NO2 was created\n");
}

main (int argc, char *argv[])
{
  int i, type;
  uint32 handle;			//Handle of the shared page
  sem_t spage;      	                //Various semaphores

  if(argc!=4)
  {
    Printf("Usage: ");
    Printf(argv[0]);
    Printf(" handle_str spage_str semaphore_str\n");
    exit();
  }
  handle = dstrtol(argv[1], NULL, 10);	//Get the handle from the arguments
  spage = dstrtol(argv[2], NULL, 10);	//Get semaphore spage
  type = dstrtol(argv[3], NULL, 10);	//Getting type

  db = (DB *)shmat(handle);		//Map the shared page to address spac
  if(db == NULL)
  {
    Printf("Could not map the virtual address to the memory, exiting...\n");
    exit();
  }
  switch (type){
      case 0: {
	oReady();
	break;
      }
      case 1:{
	nReady();
	break;
      }
      case 2:{
	makeOxygen();
	break;
      }
      case 3:{
	makeNO2();
	break;
      }
    }
  //Now let us wake up the calling process so that it can quit
  if(sem_signal(spage))
  {
    Printf("Bad semaphore spage.... Exiting!\n");
    exit();
  }
}
