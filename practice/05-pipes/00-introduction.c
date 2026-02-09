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
        // printf("%d", errno);
        // if (errno == ENOMEM) {
        //     // custom handling if no memory
        // }
        perror("fork");
    }

    if (pid == 0) {
        // Child (P1)
        // write(fds[1], "hi from child\n", strlen("hi from child\n"));

        close(fds[0]);

        // close(STDOUT_FILENO);
        // dup(fds[1]);
        dup2(fds[1], STDOUT_FILENO);
        close(fds[1]);

        execlp("ls", "ls", "-la", NULL);
        return 0;
    }

    if (pid > 0) {
        // Parent (P2)
        // char buf[14];
        // read(fds[0], buf, 14);
        // printf("read from parent: %s", buf);

        close(fds[1]);
        dup2(fds[0], STDIN_FILENO);
        close(fds[0]);

        execlp("grep", "grep", "r-x", NULL);
        return 0;
    }

    // printf("hi");
    return 0;
}
