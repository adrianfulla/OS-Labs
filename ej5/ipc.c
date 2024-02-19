#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Parametros no validos: %s <n> <x>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    char x = argv[2][0];

    printf("Hola, soy %c con el numero %d\n", x, n);

    int shm_fd = shm_open("mem_compartida", O_RDWR, 0666);
    if (shm_fd < 0) {
        shm_fd = shm_open("mem_compartida", O_RDWR | O_CREAT, 0666);
        if (shm_fd < 0) {
            perror("Error en shm_open");
            exit(EXIT_FAILURE);
        }
        printf("%c: Se ha creado una nueva memoria compartida %d\n", x, shm_fd);
        if (ftruncate(shm_fd, 128) == -1) {
            perror("ftruncate");
            exit(EXIT_FAILURE);
        }
        printf("%c: Inicializacion de memoria compartida\n", x);
    } else {
        printf("%c: Conectado a la memoria compartida existente %d\n", x, shm_fd);
    }

    char *ptr = mmap(0, 128, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("%c Error en mmap", x);
        exit(EXIT_FAILURE);
    }
    printf("%c: Ptr creado sin valor %p\n", x, (void *)ptr);

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Error en pipe");
        exit(EXIT_FAILURE);
    }

    printf("%c: La memoria compartida contiene: %s\n", x, ptr);

    pid_t pid = fork();
    if (pid < 0) {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        close(pipefd[0]);
        printf("%c: Escribiendo en memoria compartida\n", x);
        for (int i = 0; i < 128; i++) {
            if (i % n == 0) {
                write(pipefd[1], &x, 1);
            }
        }
        close(pipefd[1]);
        wait(NULL);
        printf("%c: La memoria compartida contiene: %s\n", x, ptr);
    } else {
        close(pipefd[1]);
        char buf;
        int index = 0;
        while (read(pipefd[0], &buf, 1) > 0 ) {
            ptr[index++] = buf;
            if (index >= 128) {
                break;
            }
        }
        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    }
    usleep(400000);
    munmap(ptr, 128);
    shm_unlink("mem_compartida");
    return EXIT_SUCCESS;
}
