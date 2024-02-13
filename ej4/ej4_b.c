#include <stdio.h>

#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Error al crear el proceso hijo\n");
        exit(-1);
    } else if (pid == 0) {
        for (int i = 1; i <= 4000000000; i++){
            printf("%d\n", i);
        }
        exit(0);
    } else {
        wait(NULL);
        while (1) {}
    }
}