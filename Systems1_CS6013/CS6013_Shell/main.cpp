#include <iostream>
#include "shelpers.h"
#include <readline/readline.h>

int main() {
    //initialize a buffer
    char *prompt;
    //allow for tab completion
    while ((prompt = readline("> ")) != nullptr) {
        //add prompt to history and allow access to history
        if (strlen(prompt) > 0) {
            add_history(prompt);
        }
        pid_t status = waitpid(-1, 0, WNOHANG);
        // allow for background processing
        if (status > 0) {
            waitpid(status, 0, 0);
            std::cout << "background process is finished";
        }

        //convert prompt to string to parse commands
        std::string s = prompt;
        if (s == "exit") {
            break;
        }
        //tokenize the string and get the commands
        std::vector<Command> cmds = getCommands(tokenize(s));

        //iterate through commands. If command is cd than go to home environment
        for (int i = 0; i < cmds.size(); i++) {
            if (cmds[i].exec == "cd") {
                if (cmds[i].argv.size() < 3) {
                    chdir(getenv("HOME"));
                } else {
                    chdir(cmds[i].argv[1]);
                }
                continue;
            }
            // fork
            pid_t pid = fork();

            //in the child
            if (pid == 0) {
                // handdle IO redirection for reading
                if (cmds[i].fdStdin != 0) {
                    int ret = dup2(cmds[i].fdStdin, 0);
                    if (ret < 0) {
                        perror("invalid file");
                        exit(ret);
                    }
                }
                // handdle IO redirection for writing
                if (cmds[i].fdStdout != 1) {
                    int ret = dup2(cmds[i].fdStdout, 1);
                    if (ret < 0) {
                        perror("invalid file");
                        exit(ret);
                    }
                }
                //exec
                int ret = execvp(cmds[i].exec.c_str(), const_cast<char *const *>(cmds[i].argv.data()));
                if (ret < 0) {
                    perror("invalid execvp");
                    exit(ret);
                }
            }
                //in the parent
            else if (pid > 0) {
                // parent waits if background processing is false
                if (!cmds[i].background == true) {
                    wait(NULL);
                }

                //keep running after using the pipe
                if (cmds[i].fdStdin != 0) close(cmds[i].fdStdin);
                if (cmds[i].fdStdout != 1) close(cmds[i].fdStdout);
            } else {
                perror("fork failed");
                _exit(2); //exit failure, hard
            }
        }
    }
    return 0;
}
