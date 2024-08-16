<?php

echo "El archivo PHP se está ejecutando correctamente.";
echo "El archivo PHP se está ejecutando correctamente.";
echo "El archivo PHP se está ejecutando correctamente.";
echo "El archivo PHP se está ejecutando correctamente.";
echo "El archivo PHP se está ejecutando correctamente.";
echo "El archivo PHP se está ejecutando correctamente.";
echo "El archivo PHP se está ejecutando correctamente.";
echo "El archivo PHP se está ejecutando correctamente.";
echo "El archivo PHP se está ejecutando correctamente.";

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    // Directorio donde se guardará el archivo subido
    $uploadDir = 'uploaded_files/';

    // Crear el directorio si no existe
    if (!is_dir($uploadDir)) {
        mkdir($uploadDir, 0777, true);
    }

    // Obtener información del archivo subido
    $uploadFile = $uploadDir . basename($_FILES['file']['name']);

    // Intentar mover el archivo subido al directorio de destino
    if (move_uploaded_file($_FILES['file']['tmp_name'], $uploadFile)) {
        echo "El archivo ha sido subido correctamente.";
    } else {
        echo "Hubo un error al subir el archivo.";
    }
}
?>
