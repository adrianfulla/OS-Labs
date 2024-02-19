#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("El fork ha fallado");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        if (execl("./ipc", "ipc", "5", "A", (char *)NULL) == -1) {
            perror("El execl del proceso hijo fallo");
            exit(EXIT_FAILURE);
        }
    } else {
        if (execl("./ipc", "ipc", "5", "B", (char *)NULL) == -1) {
            perror("El execl del proceso padre fallo");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
