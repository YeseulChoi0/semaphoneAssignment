#include "header.h"

void create() {
    printf("Let\'s CREATE!\n");
    int semd;
    int v, r;
    char input[3];

    semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    if (semd == -1) {
        semd = semget(KEY, 1, 0);
        v = semctl(semd, 0, GETVAL, 0);
        printf("Semaphore already exists\n");
    }
    else {
        union semun us;
        us.val = 1;
        r = semctl(semd, 0, SETVAL, us);
        printf("Created semaphore!\n");
    }

    int shmd;
    char * data;
    shmd = shmget(KEY, SEG_SIZE, IPC_CREAT | 0644);
    data = shmat(shmd, 0, 0);
    printf("Shared memory has been created.\n");

    f = fopen(FILENAME,"w");
    printf("File has been created.\n");
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
