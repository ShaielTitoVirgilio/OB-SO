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

RUN chmod 600 /root/.ssh/id_rsa

# Permisos para cron
RUN chmod 0644 /etc/cron.d/backup-cron

# Crear carpeta para logs de cron
RUN touch /var/log/cron.log

CMD cron && tail -f /var/log/cron.log
