#include <stdio.h>
#include <unistd.h>

int main()
{
    for (int i = 0; i < 4; i++) 
    {
        pid_t pid = fork();
        printf("fork %d %d\n", i+1, pid);
    }
    return 0;
}