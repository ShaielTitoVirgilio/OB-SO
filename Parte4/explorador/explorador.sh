#!/bin/bash

# Directorio donde se montan los backups consolidados
BACKUP_DATA_DIR="/home/backup_data"
# Archivo de log para las alertas
ALERTS_LOG_FILE="/home/alertas_detectadas/alertas.log"
# Archivo para almacenar los hashes de los archivos ya procesados
PROCESSED_FILES_LOG="/home/alertas_detectadas/.processed_files.log"
# Intervalo de espera entre cada ciclo de monitoreo (en segundos)
SLEEP_INTERVAL=120

# Asegurarse de que el directorio de alertas exista
mkdir -p "$(dirname "$ALERTS_LOG_FILE")"

# Crear el archivo de log de archivos procesados si no existe
touch "$PROCESSED_FILES_LOG"

echo "Iniciando monitoreo de backups para alertas..."

while true; do
    echo "$(date): Iniciando ciclo de monitoreo..."
    
    # Verificar si existe el directorio de backup
    if [ ! -d "$BACKUP_DATA_DIR" ]; then
        echo "$(date): Directorio $BACKUP_DATA_DIR no existe, esperando..."
        sleep "$SLEEP_INTERVAL"
        continue
    fi
    
    # Iterar sobre cada directorio de máquina dentro de BACKUP_DATA_DIR
    for machine_dir in "$BACKUP_DATA_DIR"/*/; do
        if [ -d "$machine_dir" ]; then # Asegurarse de que sea un directorio
            machine_name=$(basename "$machine_dir")
            echo "$(date): Procesando máquina: $machine_name"
            
            # Buscar archivos en el directorio de la máquina y sus subdirectorios
            find "$machine_dir" -type f -print0 | while IFS= read -r -d $'\0' file; do
                echo "$(date): Revisando archivo: $file"
                
                # Calcular el hash MD5 del archivo para verificar si ya fue procesado
                file_hash=$(md5sum "$file" | awk '{print $1}')
                
                # Verificar si el archivo ya fue procesado (o si su contenido no ha cambiado)
                if ! grep -q "$file_hash" "$PROCESSED_FILES_LOG"; then
                    echo "$(date): Archivo nuevo o modificado: $file"
                    
                    # Si el archivo contiene la palabra "Alarma" (insensible a mayúsculas/minúsculas)
                    if grep -qi "Alarma" "$file" 2>/dev/null; then
                        echo "$(date): alarma encontrada en: $file"
                        
                        # Obtener hora y fecha local
                        current_datetime=$(date +"%Y-%m-%d %H:%M:%S")
                        
                        # Contar la cantidad total de palabras
                        total_words=$(wc -w < "$file")
                        
                        # Contar la cantidad de palabras que finalizan con 'a' (insensible a mayúsculas/minúsculas)
                        # Usamos grep -o para obtener cada palabra en una línea separada
                        # Luego grep -i 'a$' para filtrar las que terminan en 'a' (insensible)
                        # Y wc -l para contar las líneas (palabras)
                        words_ending_with_a=$(grep -oiE '\b[[:alnum:]]*a\b' "$file" | wc -l)
                        
                        # Registrar la alerta en el archivo de log
                        echo "[$current_datetime] ALERTA: 'Alarma' encontrada en '$file'. Palabras totales: $total_words, Palabras terminadas en 'a': $words_ending_with_a" >> "$ALERTS_LOG_FILE"
                    fi
                    
                    # Registrar el hash del archivo como procesado
                    echo "$file_hash" >> "$PROCESSED_FILES_LOG"
                else
                    echo "$(date): Archivo ya procesado: $file"
                fi
            done
        else
            echo "$(date): No se encontró directorio válido: $machine_dir"
        fi
    done
    
    echo "$(date): Monitoreo completado. Esperando $SLEEP_INTERVAL segundos para la próxima revisión"
    sleep "$SLEEP_INTERVAL"
done