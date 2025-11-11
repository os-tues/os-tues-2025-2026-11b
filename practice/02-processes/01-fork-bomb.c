#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int a[2000];
    while (1)
    {
        if (fork() == -1)
        {
            perror("fork");
        }

        if (fork() == -1)
        {
            perror("fork");
        }
    }

    return 0;
}
