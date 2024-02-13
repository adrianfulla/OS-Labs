#include <stdio.h>

#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Error al crear el proceso hijo\n");
        exit(-1);
    } else if (pid == 0) {
        printf("Mensaje del proceso hijo\n");
        exit(0);
    } else {
        wait(NULL);
        while (1) {}
    }
}