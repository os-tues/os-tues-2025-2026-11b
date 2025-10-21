#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/errno.h>

int main(int argc, char const *argv[])
{
    // Relative file path, equivalent to 
    const char file_path[] = "../01-files/example-files/example.txt";

    // Open the file for writing. Create the file if it doesn't exist.
    // 0640 is the octal representation of rwx permissions - |110|100|000|
    //                                                        ↓↓↓ ↓↓↓ ↓↓↓
    //                         |owner|group|everyone else| - |rw-|r--|---|
    int fd = open(file_path, O_WRONLY | O_CREAT, 0640);
    if (fd == -1) {     // open syscall failed
        perror("open"); // prints the errno in a human-readable way (see `man 2 perror`)
        return 1;
    }
    return 0;
}
