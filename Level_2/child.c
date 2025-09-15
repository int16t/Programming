#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int main(){

    pid_t child;

    child = fork();

    if (child == 0){
        printf("I am the child process with PID: %d\n", getpid());
        return 0;
    } 
    else if (child == -1){
        printf("Fork failed\n");
        return 1;
    }
    else {
        printf("I am the parent process with PID: %d and my child's PID is: %d\n", getpid(), child);
    }

    wait(NULL);
    sleep(1);

    printf("--------------------------------\n");
    printf("Creating another 10 processes...\n");
    printf("--------------------------------\n");

    pid_t processes[10];
    for (int i = 0; i < 10; i++){
        processes[i] = fork();

        if (processes[i] == 0){
            printf("I am process number %d with PID: %d\n", i + 1, getpid());
            return 0; // Child process exits after printing
        } 
        else if (processes[i] == -1){
            printf("Fork failed for process number %d\n", i + 1);
        }
    }

    for (int i = 0; i < 10; i++) {
        waitpid(processes[i], NULL, 0);
    }
   
    return 0;
}