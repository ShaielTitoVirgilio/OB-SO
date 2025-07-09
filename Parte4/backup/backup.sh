#!/bin/bash
set -e

echo "$(date): Iniciando backup..."

# Defino las máquinas y las carpetas de origen del backup
declare -A maquinas
maquinas["maquina1"]="/home/users/documentos"
maquinas["maquina2"]="/home/users/documentos"
maquinas["maquina3"]="/home/users/documentos"

# Carpeta donde guardamos los backups consolidados
backup_dir="/home/backup_data"

for maquina in "${!maquinas[@]}"
do
  src="${maquinas[$maquina]}"
  dest="$backup_dir/$maquina"
  
  mkdir -p "$dest"
  
  # En lugar de rsync local, copiamos desde las carpetas montadas
  # Las máquinas se montan en /home/maquina1, /home/maquina2, etc.
  actual_src="/home/$maquina"
  
  echo "$(date): Procesando backup de $maquina desde $actual_src a $dest"
  
  # Rsync sin traer archivos que ya tenemos (solo cambios)
  if [ -d "$actual_src" ]; then
    rsync -avz --delete "$actual_src/" "$dest/"
    echo "$(date): Backup completado para $maquina"
  else
    echo "$(date): Advertencia: No se encontró directorio $actual_src"
  fi
done

echo "$(date): Backup terminado."
