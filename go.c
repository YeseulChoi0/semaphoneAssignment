#include "header.h"

int main() {
    int semd = semget(KEY, 1, 0);
    int shmd = shmget(KEY, 1, 0);
    struct sembuf stempd;
    stempd.sem_flg = SEM_UNDO;
    stempd.sem_op = -1;
    stempd.sem_num = 0;
    if(semd == -1) {
            printf("Semaphore does not exist.\n");
    }
    if(shmd == -1) {
            printf("Shared memory does not exist.\n");
            stempd.sem_op = 1;
            semop(semd, &stempd, 1);
    }

    char *mem;
    mem = shmat(shmd,0,0);
    printf("Last addition: %s\n", mem);
    printf("New addition: ");
    char input[SEG_SIZE];
    fgets(mem, SEG_SIZE, stdin);
    strcpy(input, mem);

    int fd = open(FILENAME, O_RDWR | O_APPEND, 644);

    write(fd, input, strlen(input));
    close(fd);

    stempd.sem_op = 1;
    semop(semd, &stempd, 1);
    shmdt(mem);
}
