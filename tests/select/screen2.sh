#!/bin/bash


#funcionamiento en terminales
# ./webserver configurationFiles/examen.conf 
# ./run_select.sh 
# tail -f /tmp/*.log
# siege -b http://127.0.0.1:8080
# curl -i -X POST \
#       -H "Content-Type: multipart/form-data; boundary=-------------------------$(date +%s)" \
#        -F "fileToUpload=@84mb.mp4" \
#        http://127.0.0.1:8080/upload \
#        --limit-rate 50K \
#        -o "response.txt"





# Función para ejecutar un comando en segundo plano
run_command() {
    (
        echo "Iniciando $2 en $(date)"
        $1
        echo "Finalizando $2 en $(date)"
    ) > /tmp/$2.log 2>&1 &
    echo "Comando $2 iniciado. PID: $!"
}


# Ejecuta todos los comandos simultáneamente
run_command "curl -i -X GET http://127.0.0.1:8080/bigfile.txt --limit-rate 50K --output big1.txt" "curl1"
run_command "curl -i -X GET http://127.0.0.1:8080/bigfile.txt --limit-rate 75K --output big2.txt" "curl2"
run_command "curl -i -X GET http://127.0.0.1:8080/bigfile.txt --limit-rate 100K --output big3.txt" "curl3"
run_command "curl -i -X GET http://127.0.0.1:8080/bigfile.txt --limit-rate 125K --output big4.txt" "curl4"


echo "Todos los comandos han sido iniciados."
echo "Para ver la salida de un comando específico, usa 'tail -f /tmp/[nombre_comando].log'"
echo "Por ejemplo: tail -f /tmp/siege.log"
echo "Por ejemplo: tail -f /tmp/*.log"
# Espera a que el usuario presione Enter para terminar
read -p "Presiona Enter para terminar todos los procesos..."

# Termina todos los procesos en segundo plano
pkill -P $$

echo "Todos los procesos han sido terminados."

