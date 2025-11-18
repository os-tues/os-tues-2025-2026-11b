#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        char err[] = "Invalid number of arguments.\n";
        write(STDERR_FILENO, err, strlen(err) + 1);
        return 1;
    }

    while (1)
    {
        int pid = fork();

        if (pid == -1)
        {
            perror("fork");
            return 1;
        }

        if (pid == 0)
        {
            // Child proccess
            // printf("child proccess\n");

            // if (execlp("/bin/lsdlksajgf", "/bin/ls", "-l", "-a", NULL) == -1) {
            // execlp(argv[1], argv[1], "-l", "-a", NULL);
            execv(argv[1], &argv[1]);
            perror("exec");
            return 1;
            // }
        }

        if (pid > 0)
        {
            // Parent proccess
            // printf("parent proccess\n");
            int status;
            waitpid(pid, &status, 0);
            sleep(2);
            printf("\n\nnstatus: %d\n\n", status);
            // printf("child proccess is done\n");
        }
    }

    return 0;
}
