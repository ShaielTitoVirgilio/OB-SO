#!/bin/bash

html_file="/var/www/html/index.html"

cat << EOF > "$html_file"
<html>
<head>
<title>Backups y Alertas</title>
<style>
body { font-family: Arial, sans-serif; margin: 20px; }
h1 { color: #333; }
ul { background: #f5f5f5; padding: 10px; }
pre { background: #fffacd; padding: 10px; border: 1px solid #ddd; }
</style>
</head>
<body>
<h1>Backups realizados</h1>
<ul>
EOF

for dir in /home/backup_data/*/; do
  maquina=$(basename "$dir")
  echo "<li>$maquina</li>" >> "$html_file"
done

cat << EOF >> "$html_file"
</ul>

<h1>Alertas detectadas</h1>
<pre>
$(if [ -f /home/alertas_detectadas/alertas.log ] && [ -s /home/alertas_detectadas/alertas.log ]; then
    cat /home/alertas_detectadas/alertas.log
else
    echo "No hay alertas detectadas aún."
    echo ""
    echo "Debug info:"
    echo "- Archivo alertas.log existe: $([ -f /home/alertas_detectadas/alertas.log ] && echo "SÍ" || echo "NO")"
    echo "- Tamaño del archivo: $([ -f /home/alertas_detectadas/alertas.log ] && wc -c < /home/alertas_detectadas/alertas.log || echo "0") bytes"
    echo "- Directorio backup_data existe: $([ -d /home/backup_data ] && echo "SÍ" || echo "NO")"
    echo "- Contenido backup_data:"
    ls -la /home/backup_data/ 2>/dev/null || echo "  (vacío o no accesible)"
    echo "- Archivos procesados:"
    wc -l < /home/alertas_detectadas/.processed_files.log 2>/dev/null || echo "  0"
fi)
</pre>
</body>
</html>
EOF
