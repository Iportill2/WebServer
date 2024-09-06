test_request() {
    local method=$1
    local path=$2
    local host="127.0.0.1"
    local port="8080"

    # Construir la solicitud HTTP
    request="${method} ${path} HTTP/1.\r\nHost: ${host}:${port}\r\n\r\n"

    # Enviar la solicitud a través de telnet y capturar la respuesta completa
    response=$(echo -e "$request" | telnet $host $port 2>/dev/null)
    sleep 1
    # Mostrar la respuesta completa (cabeceras + cuerpo)
    echo "Respuesta:"
    echo "$response"
}

# Llamar a la función para mostrar la página index.html
test_request "GET" "/index.html"
