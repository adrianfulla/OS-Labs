#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <omp.h>

char sudoku[9][9];

bool filas_validas = false;
bool columnas_validas = false;
bool grupos_validas = false;

void *revisarFilas(void *arg) {
    omp_set_nested(true);
    long thread_id = syscall(SYS_gettid);
    printf("El thread que ejecuta el metodo para ejecutar el metodo de revision de filas es: %ld\n", thread_id);
    omp_set_num_threads(9);
    #pragma omp parallel for //schedule(dynamic)
    for (int i = 0; i < 9; i++) {
        long thread_id = syscall(SYS_gettid);
        printf("En la revision de filas el siguiente es un thread en  ejecucion: %ld\n", thread_id);
        bool nums[10] = {false};
        #pragma omp parallel for //schedule(dynamic)
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] < '1' || sudoku[i][j] > '9') {
                printf("\nError: La fila contiene caracteres no válidos.\n");
                pthread_exit(NULL);
            }
            int num = sudoku[i][j] - '0';
            if (nums[num]) {
                printf("\nError: La fila no cumple con las reglas del Sudoku.\n");
                pthread_exit(NULL);
            }
            nums[num] = true;
        }
    }
    filas_validas = true;
    pthread_exit(NULL);
}

void *revisarColumnas(void *arg) {
    omp_set_nested(true);
    long thread_id = syscall(SYS_gettid);
    printf("El thread que ejecuta el metodo para ejecutar el metodo de revision de columnas es: %ld\n", thread_id);
    omp_set_num_threads(9);
    #pragma omp parallel for //schedule(dynamic)
    for (int i = 0; i < 9; i++) {
        long thread_id = syscall(SYS_gettid);
        printf("En la revision de columnas el siguiente es un thread en  ejecucion: %ld\n", thread_id);
        bool nums[10] = {false};
        #pragma omp parallel for //schedule(dynamic)
        for (int j = 0; j < 9; j++) {
            if (sudoku[j][i] < '1' || sudoku[j][i] > '9') {
                printf("\nError: La columna contiene caracteres no válidos.\n");
                pthread_exit(NULL);
            }
            int num = sudoku[j][i] - '0';
            if (nums[num]) {
                printf("\nError: La columna no cumple con las reglas del Sudoku.\n");
                pthread_exit(NULL);
            }
            nums[num] = true;
        }
    }
    columnas_validas = true;
    pthread_exit(NULL);
}

void *revisarGrupos(void *arg) {
    omp_set_nested(true);
    long thread_id = syscall(SYS_gettid);
    printf("El thread que ejecuta el metodo para ejecutar el metodo de revision de grupos es: %ld\n", thread_id);
    omp_set_num_threads(9);
    #pragma omp parallel for //schedule(dynamic)
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            long thread_id = syscall(SYS_gettid);
            printf("En la revision de grupos el siguiente es un thread en  ejecucion: %ld\n", thread_id);
            bool nums[10] = {false};
            #pragma omp parallel for //schedule(dynamic)
            for (int k = i; k < i + 3; k++) {
                #pragma omp parallel for //schedule(dynamic)
                for (int l = j; l < j + 3; l++) {
                    printf("%c", sudoku[k][l]); // Ahora accediendo correctamente con índices bidimensionales
                    if (sudoku[k][l] < '1' || sudoku[k][l] > '9') { // Comparando caracteres correctamente
                        printf("\nError: El grupo contiene caracteres no válidos.\n");
                        pthread_exit(NULL);
                    }
                    int num = sudoku[k][l] - '0'; // Tratando sudoku[k][l] como un carácter
                    if (nums[num]) {
                        printf("\nError: El grupo no cumple con las reglas del Sudoku.\n");
                        pthread_exit(NULL);
                    }
                    nums[num] = true;
                }
            }
        }
    }
    grupos_validas = true;
    pthread_exit(NULL);
}



int main() {
    omp_set_num_threads(1);
    omp_set_nested(true);
    int fd = open("sudoku", O_RDONLY);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        return 1;
    }
    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("Error al obtener el tamaño del archivo");
        close(fd);
        return 1;
    }
    off_t size = st.st_size;
    
    char *sudoku_data = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (sudoku_data == MAP_FAILED) {
        perror("Error al mapear el archivo a la memoria");
        close(fd);
        return 1;
    }

    #pragma omp parallel for //schedule(dynamic)
    for (int i = 0; i < 81; i++) {
        sudoku[i / 9][i % 9] = sudoku_data[i];
    }
    
    pthread_t columnas_thread;
    if (pthread_create(&columnas_thread, NULL, revisarColumnas, NULL)) {
        perror("Error al crear el hilo de revisar columnas");
        return 1;
    }
    pthread_t filas_thread;
    if (pthread_create(&filas_thread, NULL, revisarFilas, NULL)) {
        perror("Error al crear el hilo de revisar filas");
        return 1;
    }
    pthread_t grupos_thread;
    if (pthread_create(&grupos_thread, NULL, revisarGrupos, NULL)) {
        perror("Error al crear el hilo de revisar grupos");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Error al ejecutar fork");
        return 1;
    } else if (pid == 0) {
        char parent_proc[10];
        snprintf(parent_proc, sizeof(parent_proc), "%d", getppid());
        execlp("ps", "ps", "-p", parent_proc, "-lLf", NULL);
        perror("Error al ejecutar ps en el hijo");
        return 1;
    } else {
        wait(NULL);
    }
        
    if (pthread_join(columnas_thread, NULL)) {
        perror("Error al esperar el hilo de revisar columnas");
        return 1;
    }
    if (pthread_join(filas_thread, NULL)) {
        perror("Error al esperar el hilo de revisar filas");
        return 1;
    }
    if (pthread_join(grupos_thread, NULL)) {
        perror("Error al esperar el hilo de revisar grupos");
        return 1;
    }

    long thread_id = syscall(SYS_gettid);
    printf("El thread que ejecuta main es: %ld\n", thread_id);
    

    if (filas_validas && columnas_validas && grupos_validas) {
        printf("\nLa solución al Sudoku es válida.\n");
    } else {
        printf("\nEl Sudoku no tiene una solución válida.\n");
    }
    printf("\nAntes de terminar el estado de este proceso y sus threas es:\n");
    
    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("Error al ejecutar fork");
        return 1;
    } else if (pid1 == 0) {
        char parent_proc[10];
        snprintf(parent_proc, sizeof(parent_proc), "%d", getppid());
        execlp("ps", "ps", "-p", parent_proc, "-lLf", NULL);
        perror("Error al ejecutar ps en el hijo");
        return 1;
    } else {
        wait(NULL);
    }
    
    munmap(sudoku_data, size);
    close(fd);
    
    return 0;
}
