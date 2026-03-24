#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#define BYTES_TO_READ 10

int main(int argc, char const *argv[])
{
    const char fifo_path[] = "./fifo";
    int fd = open(fifo_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    int bytes_read;
    do {
        char buf[BYTES_TO_READ] = {0};
        bytes_read = read(fd, buf, BYTES_TO_READ);
        write(STDOUT_FILENO, buf, bytes_read);
    } while (bytes_read > 0);

    close(fd);
    return 0;
}
