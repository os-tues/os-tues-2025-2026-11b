#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    const char fifo_path[] = "./fifo";
    if (mkfifo(fifo_path, 0640) == -1) {
        if (errno != EEXIST) {
            perror("mkfifo");
            return 1;
        } else {
            printf("Fifo already exists, skipping creation...\n");
        }
    }

    int fd = open(fifo_path, O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    write(fd, "hi from producer\n", 17);

    close(fd);

    // unlink("./fifo");
    return 0;
}
