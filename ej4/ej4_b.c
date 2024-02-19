#include <stdio.h>

#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Error al crear el proceso hijo\n");
    } else if (pid == 0) {
        for (int i = 1; i <= 40000000; i++){
            printf("%d\n", i);
        }
    } else {
        while (1) {}
    }
}