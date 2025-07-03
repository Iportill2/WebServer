# WebServer - Proyecto 42

![42 School](https://img.shields.io/badge/42-School-000000?style=flat&logo=42&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat&logo=c%2B%2B&logoColor=white)
![HTTP](https://img.shields.io/badge/HTTP-1.1-blue)

Un servidor HTTP/1.1 completo implementado en C++98, diseñado para manejar múltiples conexiones concurrentes y cumplir con los estándares web modernos.

## 📋 Tabla de Contenidos

- [Características](#-características)
- [Instalación](#-instalación)
- [Uso](#-uso)
- [Configuración](#-configuración)
- [Estructura del Proyecto](#-estructura-del-proyecto)
- [Ejemplos](#-ejemplos)
- [Testing](#-testing)
- [Autores](#-autores)

## ✨ Características

### Funcionalidades Principales
- ✅ **Servidor HTTP/1.1** compliant
- ✅ **Múltiples servidores virtuales** en diferentes puertos
- ✅ **Métodos HTTP**: GET, POST, DELETE
- ✅ **CGI support** para scripts dinámicos
- ✅ **File upload/download** con gestión de archivos
- ✅ **Autoindex** para listado de directorios
- ✅ **Error pages** personalizables
- ✅ **Redirects** (301, 302, 303, etc.)
- ✅ **Body size limits** configurables
- ✅ **Multiple locations** por servidor
- ✅ **Static file serving** optimizado

### Características Técnicas
- ⚡ **Non-blocking I/O** con `select()`
- 🔧 **Configuración flexible** mediante archivos .conf
- 🛡️ **Error handling** robusto
- 📁 **Directory traversal** protection
- 🎯 **Memory management** sin leaks
- 🔄 **Signal handling** (SIGINT, SIGTERM)

## 🚀 Instalación

### Prerrequisitos
- **Compilador**: g++ o clang++ con soporte C++98
- **Sistema**: Linux/macOS
- **Make**: GNU Make

### Compilación
```bash
# Clonar el repositorio
git clone [url-del-repo]
cd WebServer

# Compilar el proyecto
make

# Limpiar archivos objeto
make clean

# Limpiar completamente
make fclean

# Recompilar desde cero
make re
```

## 🎮 Uso

### Inicio Básico
```bash
# Usar configuración por defecto
./webserv

# Usar archivo de configuración específico
./webserv conf/1.conf

# Ejemplo con múltiples servidores
./webserv conf/2.conf
```

### Acceso a los Servicios
```bash
# Servidor principal (puerto 8020)
curl http://localhost:8020/

# Página con fotos de los autores
curl http://localhost:8020/

# Página landing
curl http://localhost:8020/landing_page

# Upload de archivos
curl -X POST -F "file=@ejemplo.txt" http://localhost:8020/upload

# Test CGI
curl http://localhost:8020/cgi-bin/script.cpp

# Autoindex
curl http://localhost:8020/autoindex/
```

## ⚙️ Configuración

### Estructura del Archivo de Configuración

```nginx
server {
    listen      0.0.0.0:8020;
    server_name localhost;
    body_size   10000;
    root        ./pagina;

    location / {
        root     ./pagina;
        file     index.html;
        methods  get post;
    }

    location /upload {
        methods  post;
        root     ./uploads;
    }

    location /cgi-bin/ {
        cgi      on;
        methods  get post;
        root     ./cgi-bin;
    }

    location /redirect {
        redirect 302 https://example.com/;
    }
}
```

### Directivas Disponibles

#### Servidor
- `listen`: IP y puerto del servidor
- `server_name`: Nombre del servidor virtual
- `body_size`: Tamaño máximo del body (bytes)
- `root`: Directorio raíz por defecto

#### Location
- `root`: Directorio raíz para esta location
- `file`: Archivo por defecto a servir
- `methods`: Métodos HTTP permitidos
- `autoindex`: Activar listado de directorios
- `cgi`: Habilitar procesamiento CGI
- `redirect`: Redirección HTTP
- `internal`: Location solo accesible internamente

## 📁 Estructura del Proyecto

```
WebServer/
├── src/                    # Código fuente principal
│   ├── main.cpp           # Punto de entrada
│   ├── Server.cpp/hpp     # Servidor principal
│   ├── Config.cpp/hpp     # Parser de configuración
│   ├── Request.cpp/hpp    # Parsing de requests HTTP
│   ├── Response.cpp/hpp   # Generación de responses
│   ├── Cgi.cpp/hpp       # Manejo de CGI
│   ├── Load.cpp/hpp      # Upload de archivos
│   ├── Download.cpp/hpp  # Download de archivos
│   ├── Delete.cpp/hpp    # Método DELETE
│   ├── Autoindex.cpp/hpp # Listado de directorios
│   └── ErrorPage.cpp/hpp # Páginas de error
├── conf/                  # Archivos de configuración
│   ├── 1.conf            # Configuración básica
│   ├── 2.conf            # Múltiples servidores
│   └── 1iker.conf        # Configuración con landing
├── cgi-bin/              # Scripts CGI
├── pagina/               # Contenido web principal
├── landing_page/         # Página de presentación
├── uploaded_files/       # Archivos subidos
└── errors/               # Páginas de error personalizadas
```

## 🧪 Testing

### Tests Básicos
```bash
# Test de conectividad
curl -v http://localhost:8020/

# Test de métodos HTTP
curl -X GET http://localhost:8020/
curl -X POST -d "data=test" http://localhost:8020/upload
curl -X DELETE http://localhost:8020/delete/file.txt

# Test de upload
curl -X POST -F "file=@test.txt" http://localhost:8020/upload

# Test de CGI
curl http://localhost:8020/cgi-bin/script.cpp
```

### Tests de Stress
```bash
# Apache Bench
ab -n 1000 -c 10 http://localhost:8020/

# Siege
siege -c 10 -t 30s http://localhost:8020/

# Múltiples conexiones simultáneas
for i in {1..50}; do curl http://localhost:8020/ & done
```

### Tests de Configuración
```bash
# Test configuración inválida
./webserv conf/invalid.conf

# Test sin configuración
./webserv

# Test con configuración personalizada
./webserv conf/custom.conf
```

## 🌐 Ejemplos de Uso

### 1. Servidor de Archivos Estáticos
```nginx
server {
    listen 8020;
    root ./static;
    
    location / {
        file index.html;
        methods get;
    }
}
```

### 2. API con CGI
```nginx
server {
    listen 8030;
    
    location /api/ {
        cgi on;
        root ./api;
        methods get post;
    }
}
```

### 3. Galería de Imágenes
```nginx
server {
    listen 8040;
    
    location /gallery/ {
        autoindex on;
        methods get;
        root ./images;
    }
}
```

### 4. Upload Service
```nginx
server {
    listen 8050;
    body_size 50000000;  # 50MB
    
    location /upload {
        methods post;
        root ./uploads;
    }
}
```

## 📊 Códigos de Estado HTTP Soportados

### Success (2xx)
- `200 OK` - Solicitud exitosa
- `201 Created` - Recurso creado
- `202 Accepted` - Solicitud aceptada
- `204 No Content` - Sin contenido

### Redirection (3xx)
- `301 Moved Permanently` - Redirección permanente
- `302 Found` - Redirección temporal
- `303 See Other` - Ver otro recurso
- `304 Not Modified` - No modificado

### Client Error (4xx)
- `400 Bad Request` - Solicitud malformada
- `401 Unauthorized` - No autorizado
- `403 Forbidden` - Prohibido
- `404 Not Found` - No encontrado
- `405 Method Not Allowed` - Método no permitido
- `408 Request Timeout` - Timeout de solicitud
- `409 Conflict` - Conflicto
- `411 Length Required` - Longitud requerida
- `413 Payload Too Large` - Payload muy grande
- `414 URI Too Long` - URI muy larga
- `415 Unsupported Media Type` - Tipo de media no soportado

### Server Error (5xx)
- `500 Internal Server Error` - Error interno
- `501 Not Implemented` - No implementado
- `502 Bad Gateway` - Gateway incorrecto
- `503 Service Unavailable` - Servicio no disponible
- `505 HTTP Version Not Supported` - Versión HTTP no soportada

## 🛠️ Troubleshooting

### Problemas Comunes

#### Error de Compilación
```bash
# Verificar flags de compilación
make clean && make

# Verificar versión de C++
g++ --version
```

#### Puerto en Uso
```bash
# Verificar puertos ocupados
netstat -tulpn | grep :8020

# Matar proceso en puerto
sudo lsof -ti:8020 | xargs kill
```

#### Archivos de Configuración
```bash
# Verificar sintaxis de configuración
./webserv conf/test.conf

# Usar configuración por defecto
./webserv
```

#### Permisos de Archivos
```bash
# Verificar permisos de directorio web
ls -la pagina/

# Ajustar permisos si es necesario
chmod 755 pagina/
chmod 644 pagina/*.html
```

## 🔧 Desarrollo

### Normas de 42
- ✅ Norminette compliant
- ✅ Sin memory leaks (valgrind clean)
- ✅ Manejo adecuado de errores
- ✅ C++98 estándar
- ✅ Makefile con reglas obligatorias

### Flags de Compilación
```makefile
CFLAGS = -Wall -Werror -Wextra -std=c++98
```

### Debugging
```bash
# Compilar con debugging
make CFLAGS="-Wall -Werror -Wextra -std=c++98 -g3"

# Usar con valgrind
valgrind --leak-check=full ./webserv

# Usar con gdb
gdb ./webserv
```

## 📚 Referencias

- [RFC 7230 - HTTP/1.1 Message Syntax and Routing](https://tools.ietf.org/html/rfc7230)
- [RFC 7231 - HTTP/1.1 Semantics and Content](https://tools.ietf.org/html/rfc7231)
- [RFC 3875 - The Common Gateway Interface (CGI) Version 1.1](https://tools.ietf.org/html/rfc3875)
- [42 School - WebServ Subject](https://cdn.intra.42.fr/pdf/pdf/...)

## 👥 Autores

- **jgoikoet** - 
- **iportill2**- 

