#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#define KEY 100
#define SEG_SIZE 500
#define FILENAME "filef.txt"

FILE *f;


union semun {
   int              val;    // Value for SETVAL
   struct semid_ds *buf;    // Buffer for IPC_STAT, IPC_SET
   unsigned short  *array;  //Array for GETALL, SETALL
   struct seminfo  *__buf;  // Buffer for IPC_INFO
                               (Linux-specific)
};


void create();
void myRemove();
void view();
void execute(char * );
