import socket

def telnet_get_request(host, port, path):
    # Crear un socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        # Conectar al servidor
        s.connect((host, port))
        # Crear la solicitud GET
        request = f"GET {path} HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n"
        # Enviar la solicitud
        s.sendall(request.encode())
        # Recibir la respuesta
        response = s.recv(4096)
        print(response.decode())

# Realizar la solicitud GET a localhost:8080
telnet_get_request('localhost', 8080, '/')
