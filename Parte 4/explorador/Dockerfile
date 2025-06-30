FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    apache2 \
    bash \
    && rm -rf /var/lib/apt/lists/*

COPY explorador.sh /usr/local/bin/explorador.sh
COPY generar_html.sh /usr/local/bin/generar_html.sh

RUN chmod +x /usr/local/bin/explorador.sh /usr/local/bin/generar_html.sh

# Crear carpeta para alertas
RUN mkdir -p /home/alertas_detectadas

# Copiar index.html a apache
RUN mkdir -p /var/www/html
CMD bash -c "/usr/local/bin/explorador.sh & /usr/local/bin/generar_html.sh && apache2ctl -D FOREGROUND"
