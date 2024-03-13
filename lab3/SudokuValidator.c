#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

bool revisarFilas(const char *sudoku) {
    printf("RevisarFilas");
    for (int i = 0; i < 81; i += 9) {
        printf("\n");
        bool nums[10] = {false};
        for (int j = i; j < i + 9; j++) {
            printf("%d", sudoku[j]);
            if (sudoku[j] < '1' || sudoku[j] > '9') {
                printf("Error: La fila contiene caracteres no válidos.\n");
                return false;
            }
            int num = sudoku[j] - '0';
            if (nums[num]) {
                printf("Error: La fila no cumple con las reglas del Sudoku.\n");
                return false;
            }
            nums[num] = true;
        }
    }
    return true;
}

bool revisarColumnas(const char *sudoku) {
    printf("\nRevisarColumnas");
    for (int i = 0; i < 9; i++) {
        printf("\n");
        bool nums[10] = {false};
        for (int j = i; j < 81; j += 9) {
            printf("%d", sudoku[j]);
            if (sudoku[j] < '1' || sudoku[j] > '9') {
                printf("Error: La columna contiene caracteres no válidos.\n");
                return false;
            }
            int num = sudoku[j] - '0';
            if (nums[num]) {
                printf("Error: La columna no cumple con las reglas del Sudoku.\n");
                return false;
            }
            nums[num] = true;
        }
    }
    return true;
}

bool revisarGrupos(const char *sudoku) {
    printf("\nRevisarGrupos");
    for (int i = 0; i < 9; i += 3) {
        
        for (int j = 0; j < 9; j += 3) {
            printf("\n");
            bool nums[10] = {false}; // Array para verificar la presencia de números del 1 al 9
            for (int k = i; k < i + 3; k++) {
                for (int l = j; l < j + 3; l++) {
                    int index = k * 9 + l;
                    printf("%d", sudoku[index]);
                    if (sudoku[index] < '1' || sudoku[index] > '9') {
                        printf("Error: El grupo contiene caracteres no válidos.\n");
                        return false;
                    }
                    int num = sudoku[index] - '0';
                    if (nums[num]) {
                        printf("Error: El grupo no cumple con las reglas del Sudoku.\n");
                        return false;
                    }
                    nums[num] = true;
                }
            }
        }
    }
    return true;
}

int main() {
    const char *sudoku = "624539187519728634837614295113865729958247361762391458371956842496182573285473916";

    if (revisarFilas(sudoku) && revisarColumnas(sudoku) && revisarGrupos(sudoku)) {
        printf("El Sudoku tiene una solución válida.\n");
    } else {
        printf("El Sudoku no tiene una solución válida.\n");
    }

    return 0;
}
