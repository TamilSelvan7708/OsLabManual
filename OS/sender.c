#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of shared memory

int main() {
    key_t key = ftok("shmfile",65); // Generate unique key
    int shmid = shmget(key, SHM_SIZE, 0666|IPC_CREAT); // Create shared memory segment

    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    char *str = (char*) shmat(shmid, (void*)0, 0); // Attach to shared memory

    if (str == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    sprintf(str, "Welcome to Shared Memory"); // Write message

    sleep(5); // Delay to allow receiver to read

    shmdt(str); // Detach from shared memory

    return 0;
}