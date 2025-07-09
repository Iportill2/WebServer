
# include <sstream>
# include <iostream>
# include <string>

int toInt(const std::string &str)
{
    std::stringstream ss(str);
    int num;
    ss >> num;
    return (num);
}

void printHTMLResponse(int originalNumber, int result)
{
    // Headers HTTP
    std::cout << "Content-Type: text/html\r\n";
    std::cout << "\r\n";
    
    // Página HTML completa
    std::cout << "<!DOCTYPE html>\n";
    std::cout << "<html lang=\"es\">\n";
    std::cout << "<head>\n";
    std::cout << "    <meta charset=\"UTF-8\">\n";
    std::cout << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    std::cout << "    <title>Resultado - Super I.A.</title>\n";
    std::cout << "    <link rel=\"icon\" href=\"/42favicon.png\" type=\"image/png\">\n";
    std::cout << "    <style>\n";
    std::cout << "        * {\n";
    std::cout << "            margin: 0;\n";
    std::cout << "            padding: 0;\n";
    std::cout << "            box-sizing: border-box;\n";
    std::cout << "        }\n";
    std::cout << "        body {\n";
    std::cout << "            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;\n";
    std::cout << "            background: linear-gradient(135deg, #1e3c72 0%, #2a5298 100%);\n";
    std::cout << "            min-height: 100vh;\n";
    std::cout << "            display: flex;\n";
    std::cout << "            align-items: center;\n";
    std::cout << "            justify-content: center;\n";
    std::cout << "            padding: 20px;\n";
    std::cout << "        }\n";
    std::cout << "        .result-container {\n";
    std::cout << "            background: rgba(255, 255, 255, 0.95);\n";
    std::cout << "            backdrop-filter: blur(10px);\n";
    std::cout << "            border-radius: 20px;\n";
    std::cout << "            box-shadow: 0 25px 50px rgba(0, 0, 0, 0.15);\n";
    std::cout << "            padding: 50px;\n";
    std::cout << "            max-width: 600px;\n";
    std::cout << "            width: 100%;\n";
    std::cout << "            text-align: center;\n";
    std::cout << "            position: relative;\n";
    std::cout << "            overflow: hidden;\n";
    std::cout << "        }\n";
    std::cout << "        .result-container::before {\n";
    std::cout << "            content: '';\n";
    std::cout << "            position: absolute;\n";
    std::cout << "            top: 0;\n";
    std::cout << "            left: 0;\n";
    std::cout << "            right: 0;\n";
    std::cout << "            height: 4px;\n";
    std::cout << "            background: linear-gradient(90deg, #27ae60, #2ecc71);\n";
    std::cout << "        }\n";
    std::cout << "        .title {\n";
    std::cout << "            font-size: 2.5rem;\n";
    std::cout << "            font-weight: 700;\n";
    std::cout << "            color: #2c3e50;\n";
    std::cout << "            margin-bottom: 20px;\n";
    std::cout << "        }\n";
    std::cout << "        .result-box {\n";
    std::cout << "            background: linear-gradient(45deg, #27ae60, #2ecc71);\n";
    std::cout << "            color: white;\n";
    std::cout << "            padding: 30px;\n";
    std::cout << "            border-radius: 15px;\n";
    std::cout << "            margin: 30px 0;\n";
    std::cout << "            box-shadow: 0 10px 20px rgba(39, 174, 96, 0.3);\n";
    std::cout << "        }\n";
    std::cout << "        .calculation {\n";
    std::cout << "            font-size: 1.5rem;\n";
    std::cout << "            margin-bottom: 10px;\n";
    std::cout << "        }\n";
    std::cout << "        .result {\n";
    std::cout << "            font-size: 3rem;\n";
    std::cout << "            font-weight: 900;\n";
    std::cout << "            text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.2);\n";
    std::cout << "        }\n";
    std::cout << "        .gnu-image {\n";
    std::cout << "            max-width: 200px;\n";
    std::cout << "            height: auto;\n";
    std::cout << "            margin: 20px 0;\n";
    std::cout << "            border-radius: 10px;\n";
    std::cout << "        }\n";
    std::cout << "        .back-links {\n";
    std::cout << "            margin-top: 30px;\n";
    std::cout << "            display: flex;\n";
    std::cout << "            gap: 15px;\n";
    std::cout << "            justify-content: center;\n";
    std::cout << "            flex-wrap: wrap;\n";
    std::cout << "        }\n";
    std::cout << "        .btn {\n";
    std::cout << "            padding: 12px 25px;\n";
    std::cout << "            text-decoration: none;\n";
    std::cout << "            border-radius: 25px;\n";
    std::cout << "            font-weight: 600;\n";
    std::cout << "            transition: all 0.3s ease;\n";
    std::cout << "            display: inline-block;\n";
    std::cout << "        }\n";
    std::cout << "        .btn-primary {\n";
    std::cout << "            background: linear-gradient(45deg, #3498db, #2980b9);\n";
    std::cout << "            color: white;\n";
    std::cout << "            box-shadow: 0 5px 15px rgba(52, 152, 219, 0.3);\n";
    std::cout << "        }\n";
    std::cout << "        .btn-primary:hover {\n";
    std::cout << "            transform: translateY(-2px);\n";
    std::cout << "            box-shadow: 0 8px 25px rgba(52, 152, 219, 0.4);\n";
    std::cout << "        }\n";
    std::cout << "        .btn-secondary {\n";
    std::cout << "            background: linear-gradient(45deg, #95a5a6, #7f8c8d);\n";
    std::cout << "            color: white;\n";
    std::cout << "            box-shadow: 0 5px 15px rgba(149, 165, 166, 0.3);\n";
    std::cout << "        }\n";
    std::cout << "        .btn-secondary:hover {\n";
    std::cout << "            transform: translateY(-2px);\n";
    std::cout << "            box-shadow: 0 8px 25px rgba(149, 165, 166, 0.4);\n";
    std::cout << "        }\n";
    std::cout << "    </style>\n";
    std::cout << "</head>\n";
    std::cout << "<body>\n";
    std::cout << "    <div class=\"result-container\">\n";
    std::cout << "        <h1 class=\"title\">🤖 Super I.A. - Resultado</h1>\n";
    std::cout << "        \n";
    std::cout << "        <div class=\"result-box\">\n";
    std::cout << "            <div class=\"calculation\">" << originalNumber << " × 2 =</div>\n";
    std::cout << "            <div class=\"result\">" << result << "</div>\n";
    std::cout << "        </div>\n";
    std::cout << "        \n";
    std::cout << "        <img src=\"/landing_page/cgi/nu.jpg\" alt=\"Ñu con el resultado\" class=\"gnu-image\">\n";
    std::cout << "        \n";
    std::cout << "        <p>¡La Super I.A. ha procesado tu número con éxito!</p>\n";
    std::cout << "        <p>Como prometido, aquí está el resultado presentado sobre un ñu.</p>\n";
    std::cout << "        \n";
    std::cout << "        <div class=\"back-links\">\n";
    std::cout << "            <a href=\"/landing_page/cgi\" class=\"btn btn-primary\">🔄 Calcular Otro</a>\n";
    std::cout << "            <a href=\"/landing_page/\" class=\"btn btn-secondary\">🏠 Volver al Menú</a>\n";
    std::cout << "        </div>\n";
    std::cout << "    </div>\n";
    std::cout << "</body>\n";
    std::cout << "</html>\n";
}

int main (int argc, char **argv)
{
    if (argc != 2) {
        // Si no hay argumentos, mostrar página de error
        std::cout << "Content-Type: text/html\r\n";
        std::cout << "\r\n";
        std::cout << "<html><body><h1>Error: No se recibió ningún número</h1>";
        std::cout << "<a href=\"/landing_page/cgi\">Volver al formulario</a></body></html>";
        return 1;
    }
    
    int originalNumber = toInt(argv[1]);
    int result = originalNumber * 2;
    
    printHTMLResponse(originalNumber, result);
    
    return 0;
}