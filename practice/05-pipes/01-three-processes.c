#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/errno.h>
#include <fcntl.h>

int main(void)
{
    int fds[2];
    // if (lseek(1, 1, SEEK_SET) == -1) {
    //     printf("%d\n", errno);
    //     perror("lseek");
    //     return 1;
    // }
    pipe(fds);
    // printf("fds[0]: %d, fds[1]: %d\n", fds[0], fds[1]);

    pid_t pid = fork();
    if (pid == -1) {
        // Error

        perror("fork");
    }

    if (pid == 0) {
        // Child (P1)
        close(fds[0]);
        dup2(fds[1], STDOUT_FILENO);
        close(fds[1]);

        execlp("ls", "ls", "-la", NULL);
        return 0;
    }

    if (pid > 0) {
        // Parent (P2)
        close(fds[1]);
        dup2(fds[0], STDIN_FILENO);
        close(fds[0]);

        execlp("grep", "grep", "r-x", NULL);
        return 0;

    }
    return 0;
}
