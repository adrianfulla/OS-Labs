#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[]){
	int descriptor_origen = open(argv[1],O_RDONLY);
    if (descriptor_origen == -1){
        perror("Error al abrir el primer archivo");
        exit(1);
    }

    int descriptor_objetivo = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (descriptor_objetivo == -1){
        perror("Error al abrir el segundo archivo");
        close(descriptor_origen);
        exit(1);
    }

    char buffer[1024];
    ssize_t lectura;
    while ((lectura = read(descriptor_origen,buffer,1024))!= 0){
        int escrito = write(descriptor_objetivo,buffer,lectura);
        if (escrito == -1){
            perror("Error al escribir en el archivo");
            exit(1);
        }
    }

    close(descriptor_origen);
    close(descriptor_objetivo);
    return 0;

}
