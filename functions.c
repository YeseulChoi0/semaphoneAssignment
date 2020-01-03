#include "header.h"

void create(){
    union semun semaphore;
    semaphore.val = 0;

    printf("Let's CREATE!\n");

    int newId = semget(KEY,1,IPC_CREAT | IPC_EXCL);
    if (newId < 0){
      printf("Error: cannot make semaphore \n" );
    } else{
      semaphore.val++;
      semctl(newId, 0, SETVAL, semaphore.val);
      int fd = open(FILENAME, O_CREAT | O_TRUNC, 0644);
      if (fd < 0){
          printf("Error %s", strerror(errno));
      }
      close(fd);
    }
}

void myRemove() {
    printf("Removing...\n");
    int semd = semget(KEY, 1, 0);
    int shmd = shmget(KEY, 1, 0);

    printf("Removing shared memory...\n");
    shmctl(shmd, IPC_RMID, 0);
    printf("Removed!\n");

    printf("Removing semaphore...\n");
    semctl(semd, IPC_RMID, 0);
    printf("Removed!\n");

    view();
    remove(FILENAME);

    printf("File removed!\n");
}

void view() {
    printf("Viewing...\n");

    f = fopen(FILENAME, "r");
    char line[SEG_SIZE];

    while(fgets(line, SEG_SIZE, f)) {
            printf("%s", line);
    }

    printf("Done viewing!\n");
}

void execute(char * arg) {
    if(!strcmp(arg,"-c")) {
      create();
    }

    else if(!strcmp(arg,"-r")) {
      myRemove();
    }

    else if(!strcmp(arg,"-v")) {
      view();
    }

    else {
      printf("No mode given\n");
    }
}


int main(int argc, char *argv[]) {
    if (argc == 0){
      printf("MUST HAVE INPUT\n");
    }
    char* input = argv[1];
    execute(input);
}
