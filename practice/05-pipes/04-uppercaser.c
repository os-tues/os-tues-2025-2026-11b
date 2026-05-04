#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int pipe_fds[2];
    if (pipe(pipe_fds) == -1) {
        perror("pipe");
        return 1;
    }

    int pid = fork();
    if (pid == -1) {
        if (errno == EAGAIN) {
            // custom handling for specific error
        }
        perror("fork");
        return 1;
    }
    

    if (pid == 0) {
        // Child
        close(pipe_fds[0]);

        // close(1);
        // dup(pipe_fds[1]);
        dup2(pipe_fds[1], STDOUT_FILENO);

        close(pipe_fds[1]);
        execvp(argv[1], argv + 1);
    }

    if (pid > 0) {
        // Parent
        close(pipe_fds[1]);
        waitpid(pid, NULL, 0);
        char buff;
        while (read(pipe_fds[0], &buff, sizeof(buff)) > 0) {
            if (buff >= 'a' && buff <= 'z') {
                printf("%c", buff  + 'A' - 'a');
            } else {
                printf("%c", buff);
            }
        }
        close(pipe_fds[0]);
    }
    return 0;
}
