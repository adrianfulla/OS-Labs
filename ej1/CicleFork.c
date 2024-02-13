#include <stdio.h>
#include <unistd.h>

int main()
{
    for (int i = 1; i < 5; i++) 
    {
        pid_t pid = fork();
        printf("fork %d %d\n", i,pid);
    }
    return 0;
}