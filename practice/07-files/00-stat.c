#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>

int main(int argc, char const *argv[])
{
    struct stat file_stats;
    if (stat("./00-stat.c", &file_stats) == -1) {
        perror("stat");
    }

    printf("uid: %s\n", getpwuid(file_stats.st_uid)->pw_name);

    return 0;
}
