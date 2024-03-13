# Utiliza la imagen oficial de Ubuntu como imagen base
FROM ubuntu:latest

# Instala gcc y make, herramientas necesarias para compilar código C
RUN apt-get update && \
    apt-get install -y gcc make && \
    # Limpieza de archivos temporales y cache para reducir el tamaño de la imagen
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Establece el directorio de trabajo en /src
WORKDIR /src

# Este comando se ejecuta cuando se inicia un contenedor basado en esta imagen.
# Puedes ajustarlo según tus necesidades. Por defecto, se queda en espera para evitar que el contenedor se cierre automáticamente.
CMD ["bash"]
