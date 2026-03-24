#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int fds[2];
    if (pipe(fds) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    pid_t nested_pid = fork();
    if (nested_pid > 0) {
        // P1 & P2
        close(fds[0]);
        write(fds[1], pid > 0 ? "P1" : "P2", 2);
        close(fds[1]);
    }

    if (nested_pid == 0) {
        // P3 & P4
        close(fds[1]);

        size_t bytes_read;
        do {
            char buff[2];
            bytes_read = read(fds[0], buff, 2);
            printf("%s: %s\n", pid > 0 ? "P3" : "P4", buff);
        } while(bytes_read > 0);

        close(fds[0]);
    }

    return 0;
}
