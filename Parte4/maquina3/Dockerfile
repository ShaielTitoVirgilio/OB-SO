FROM ubuntu:22.04

# Instalar cualquier paquete necesario (puedes agregar más según tus necesidades)
RUN apt-get update && apt-get install -y \
    bash \
    && rm -rf /var/lib/apt/lists/*

# Crear el directorio donde se montarán los documentos
RUN mkdir -p /home/users/documentos

# Establecer el directorio de trabajo
WORKDIR /home/users/documentos

# Comando para mantener el contenedor corriendo
ENTRYPOINT ["tail", "-f", "/dev/null"]