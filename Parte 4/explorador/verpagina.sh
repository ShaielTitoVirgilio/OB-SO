#!/bin/bash

html_file="/var/www/html/index.html"

cat << EOF > "$html_file"
<html>
<head><title>Backups y Alertas</title></head>
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
$(cat /home/alertas_detectadas/alertas.log 2>/dev/null || echo "No hay alertas")
</pre>
</body>
</html>
EOF
