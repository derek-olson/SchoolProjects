#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {

    int fd[2];
    int status;
    pipe(fd);
    int sz = sizeof(argv[1]);

    printf("Parent: %d\n", getpid());
    pid_t pid = fork();

    if(pid < 0){
        perror("error occurred during fork, new process not created\n");
    }
    else if (pid == 0){
        //print the child pid
        printf("Child %d\n", getpid());

        // close the write end of pipe
        close(fd[1]);

        //create array to read pipe to
        char arr[sz];

        // n stores the total bytes read
        int n = read(fd[0], arr, sizeof(arr));
        for (int i = 0; i < sz; i++){
            std::cout << arr[i];
        }

        exit(0);
    }
    else if(pid > 0){

        //close the read end of pipe
        close(fd[0]);

        //write the pipe
        write(fd[1], argv[1], sizeof(argv[1]))+1;

        //wait for the child
        waitpid(pid, &status, 0);
    }
    
    else{
        perror("error\n");
    }

    return 0;
}
