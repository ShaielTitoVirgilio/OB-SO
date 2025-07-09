FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    apache2 \
    bash \
    && rm -rf /var/lib/apt/lists/*

COPY explorador.sh /usr/local/bin/explorador.sh
COPY verpagina.sh /usr/local/bin/verpagina.sh

RUN chmod +x /usr/local/bin/explorador.sh /usr/local/bin/verpagina.sh

# Crear carpeta para alertas
RUN mkdir -p /home/alertas_detectadas

# Copiar index.html a apache
RUN mkdir -p /var/www/html

# Comando que ejecuta ambos scripts en paralelo y apache
CMD bash -c "/usr/local/bin/verpagina.sh && /usr/local/bin/explorador.sh & while true; do sleep 30; /usr/local/bin/verpagina.sh; done &" && apache2ctl -D FOREGROUND

EXPOSE 80