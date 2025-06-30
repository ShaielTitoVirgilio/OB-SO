#!/bin/bash
set -e

# Defino las máquinas y las carpetas de destino del backup
declare -A maquinas
maquinas["maquina1"]="/home/maquina1"
maquinas["maquina2"]="/home/maquina2"
maquinas["maquina3"]="/home/maquina3"

# Carpeta donde guardamos los backups consolidados
backup_dir="/home/backup_data"

for maquina in "${!maquinas[@]}"
do
  src="${maquinas[$maquina]}"
  dest="$backup_dir/$maquina"
  
  mkdir -p "$dest"
  
  # Rsync sin traer archivos que ya tenemos (solo cambios)
  rsync -avz --delete "$src/" "$dest/"
done
