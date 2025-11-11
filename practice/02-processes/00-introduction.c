#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{

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
            execlp("/bin/ls", "/bin/ls", "-l", "-a", NULL);
            perror("exec");
            return 1;
            // }
        }

        if (pid > 0)
        {
            // Parent proccess
            // printf("parent proccess\n");
            waitpid(pid, NULL, 0);
            sleep(2);
            // printf("child proccess is done\n");
        }
    }

    return 0;
}
