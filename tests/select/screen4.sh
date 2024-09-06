#!/bin/bash
    curl -i -X POST \
        -H "Content-Type: multipart/form-data; boundary=-------------------------$(date +%s)" \
        -F "fileToUpload=@../84mb.mp4" \
        http://127.0.0.1:8080/upload \
        --limit-rate 50K \
        -o "response.txt"