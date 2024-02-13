#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid1 = fork();
    pid_t pid2 = fork();
    pid_t pid3 = fork();
    pid_t pid4 = fork();

    printf("fork 1 %d\n", pid1);
    printf("fork 2 %d\n", pid2);
    printf("fork 3 %d\n", pid3);
    printf("fork 4 %d\n", pid4);

}