FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    openssh-client \
    rsync \
    cron \
    && rm -rf /var/lib/apt/lists/*

# Copiar scripts y claves
COPY backup.sh /usr/local/bin/backup.sh
COPY crontab.txt /etc/cron.d/backup-cron
COPY id_rsa /root/.ssh/id_rsa
COPY id_rsa.pub /root/.ssh/id_rsa.pub

# Permisos correctos
RUN chmod +x /usr/local/bin/backup.sh
RUN chmod 600 /root/.ssh/id_rsa
RUN chmod 644 /root/.ssh/id_rsa.pub

# Permisos para cron
RUN chmod 0644 /etc/cron.d/backup-cron

# Aplicar el crontab - asegurar que termine en newline
RUN echo "" >> /etc/cron.d/backup-cron && crontab /etc/cron.d/backup-cron

# Crear carpeta para logs de cron
RUN touch /var/log/cron.log

# Ejecutar backup inmediatamente y luego iniciar cron
CMD /usr/local/bin/backup.sh && cron && tail -f /var/log/cron.log
