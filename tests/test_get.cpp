#include "test_get.hpp"
#include "tester2.hpp"
#include <iostream>

GETTest::GETTest(const std::string& server, int port, const std::string& path, 
                 const std::string& expectedStatusCode, const std::string& expectedKeyword)
    : Test(server, port, path, expectedStatusCode, expectedKeyword) {}

bool GETTest::run() {
    actualResponse = sendGETRequest(server, port, path);
    bool statusCodeMatch = actualResponse.find(expectedStatusCode) != std::string::npos;
    bool keywordMatch = actualResponse.find(expectedKeyword) != std::string::npos;
    return statusCodeMatch && keywordMatch;
}

std::string GETTest::getName() const {
    return "GET Test";
}

CurlGETTest::CurlGETTest(const std::string& server, int port, const std::string& path, 
                         const std::string& expectedStatusCode, const std::string& expectedKeyword)
    : Test(server, port, path, expectedStatusCode, expectedKeyword) {}

bool CurlGETTest::run() {
    std::string command = "curl -i -X GET 'http://" + server + ":" + std::to_string(port) + path + "'";
    std::string response = executeCurlCommand(command);
    return response.find(expectedStatusCode) != std::string::npos &&
           response.find(expectedKeyword) != std::string::npos;
}

std::string CurlGETTest::getName() const {
    return "Curl GET Test";
}

void addGETTests(TestRunner& runner) {

// 403 no me funciona, el resto si.
// el 413 es en post
// falta el 405
// falta el 414 -> Texto largo al final del fichero.
curl -I -L http://10.14.8.6:8080/ \
  --resolve theband.com:8080:10.14.8.6


    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/files/sinpermisos.jpg", "403", "Forbidden"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/files/sinpermisos.jpg", "403", "Forbidden"));

    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/bigfile.txt", "200", "AJXWebserver"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/bigfile.txt", "200", "AJXWebserver"));          
    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/", "200 OK", "Webserver"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/", "200 OK", "Webserver"));
    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/42", "301", "42urduliz"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/42", "301", "42urduliz"));
    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/buscador", "301", "google"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/buscador", "301", "google"));
    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/buscador2", "302", "google"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/buscador2", "302", "google"));
    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/buscador3", "303", "google"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/buscador3", "303", "google"));
    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/buscador4", "307", "google"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/buscador4", "307", "google"));
    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/path%20with%20spaces%20and%20special%20characters%21%40%23", "400", "Bad Request"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/path%20with%20spaces%20and%20special%20characters%21%40%23", "400", "Bad Request"));
    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/nonexistent", "404", "404 pages"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/nonexistent", "404", "404 pages"));
    runner.addTest(new GETTest(SERVER_ADDRESS, 8081, "/contact.html/", "404", "Not Found"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8081, "/contact.html/", "404", "Not Found"));    
    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/cgi-bin/Python/timeOut.py", "408", "Request Timeout"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/cgi-bin/Python/timeOut.py", "408", "Request Timeout"));
    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/assets/animate.css", "200", "Content-Type: text/css"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/assets/animate.css", "200", "Content-Type: text/css"));
    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/assets/custom.js", "200", "Content-Type: application/javascript"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/assets/custom.js", "200", "Content-Type: application/javascript"));
    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/assets/c1.jpg", "200", "Content-Type: image/jpeg"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/assets/c1.jpg", "200", "Content-Type: image/jpeg"));
    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/search?q=test&page=1", "200", "HTTP/1.1"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/search?q=test&page=1", "200", "HTTP/1.1"));
    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/this/is/a/very/long/path/that/should/still/work/correctly", "200", "HTTP/1.1"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/this/is/a/very/long/path/that/should/still/work/correctly", "200", "HTTP/1.1"));
    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/files/", "200 OK", "Directory Explorer"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/files/", "200 OK", "Directory Explorer"));
    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/cgi-bin/", "200 OK", "Python"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/cgi-bin/", "200 OK", "Python"));
    runner.addTest(new GETTest(SERVER_ADDRESS, 8080,     "/cgi-bin/Python/calculadora.py?num1=30&num2=60&operation=add", "200 OK", "90"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/cgi-bin/Python/calculadora.py?num1=30&num2=60&operation=add", "200 OK", "90"));
    runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/upload.html/", "404", "404 pages"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8080, "/upload.html/", "404", "404 pages"));
    runner.addTest(new GETTest(SERVER_ADDRESS, 8081, "/", "200 OK", "img/team-2.jpg"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8081, "/", "200 OK", "img/team-2.jpg")); 
    runner.addTest(new GETTest(SERVER_ADDRESS, 8081, "/contact.html", "200 OK", "Contact For Any Query"));
    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8081, "/contact.html", "200 OK", "Contact For Any Query")); 
      
/*

  runner.addTest(new GETTest(SERVER_ADDRESS, 8080, "/urisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooorisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooorisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooorisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooorisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooorisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooorisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargurisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooo", "414", "URI Too Large"));

    runner.addTest(new CurlGETTest(SERVER_ADDRESS, 8081, "/urisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooourisuperlargoooo", "414", "URI Too Large"));

*/



/*
    para mostrar que va cada vez al select
chmod +x screen1.sh screen2.sh screen3.sh screen4.sh screen5.sh

    siege -b http://127.0.0.1:8080

    curl -i -X GET http://127.0.0.1:8080/bigfile.txt --limit-rate 50K --output "big1.txt"
    curl -i -X GET http://127.0.0.1:8080/bigfile.txt --limit-rate 75K --output "big2.txt"
    curl -i -X GET http://127.0.0.1:8080/bigfile.txt --limit-rate 100K --output "big3.txt"
    curl -i -X GET http://127.0.0.1:8080/bigfile.txt --limit-rate 125K --output "big4.txt"
    
    curl -i -X POST \
        -H "Content-Type: multipart/form-data; boundary=-------------------------$(date +%s)" \
        -F "fileToUpload=@84mb.mp4" \
        http://127.0.0.1:8080/upload \
        --limit-rate 50K \
        -o "response.txt"




*/
}
