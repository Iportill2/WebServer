#include "test_post.hpp"
#include "tester2.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <sys/stat.h>



POSTTest::POSTTest(const std::string& server, int port, const std::string& path, 
                   const std::string& expectedStatusCode, const std::string& expectedKeyword,
                   const std::string& filename, const std::string& fileContent)
    : Test(server, port, path, expectedStatusCode, expectedKeyword),
      filename(filename), fileContent(fileContent) {}

bool POSTTest::run() {
    std::string boundary = "-------------------------" + std::to_string(std::time(nullptr));
    std::string body = "--" + boundary + "\r\n";
    body += "Content-Disposition: form-data; name=\"fileToUpload\"; filename=\"" + filename + "\"\r\n";
    body += "Content-Type: application/octet-stream\r\n\r\n";
    body += fileContent + "\r\n";
    body += "--" + boundary + "--\r\n";

    std::cout << "Sending POST request to " << server << ":" << port << path << std::endl;

    actualResponse = sendMultipartPostRequest(server, port, path, filename, body, "multipart/form-data; boundary=" + boundary);
    
    bool statusCodeMatch = actualResponse.find(expectedStatusCode) != std::string::npos;
    bool keywordMatch = actualResponse.find(expectedKeyword) != std::string::npos;

    std::cout << "Status code match: " << (statusCodeMatch ? "Yes" : "No") << std::endl;
    std::cout << "Keyword match: " << (keywordMatch ? "Yes" : "No") << std::endl;

    return statusCodeMatch && keywordMatch;
}

std::string POSTTest::getName() const {
    return "POST Test";
}

CurlPOSTTest::CurlPOSTTest(const std::string& server, int port, const std::string& path, 
                           const std::string& expectedStatusCode, const std::string& expectedKeyword,
                           const std::string& filename, const std::string& fileContent)
    : Test(server, port, path, expectedStatusCode, expectedKeyword),
      filename(filename), fileContent(fileContent) {}

bool CurlPOSTTest::run() {
    // Create a temporary file
    std::ofstream tempFile(filename);
    tempFile << fileContent;
    tempFile.close();

    std::string command = "curl -i -X POST -H \"Content-Type: multipart/form-data\" -F \"fileToUpload=@" + filename + "\" 'http://" + server + ":" + std::to_string(port) + path + "'";
    actualResponse = executeCurlCommand(command);

    // Remove the temporary file
   // std::remove(filename.c_str());

    bool statusCodeMatch = actualResponse.find(expectedStatusCode) != std::string::npos;
    bool keywordMatch = actualResponse.find(expectedKeyword) != std::string::npos;
    return statusCodeMatch && keywordMatch;
}

std::string CurlPOSTTest::getName() const {
    return "Curl POST Test";
}

POSTVariablesTest::POSTVariablesTest(const std::string& server, int port, const std::string& path, 
                                     const std::string& expectedStatusCode, const std::string& expectedKeyword,
                                     const std::string& var1Name, const std::string& var1Value,
                                     const std::string& var2Name, const std::string& var2Value)
    : Test(server, port, path, expectedStatusCode, expectedKeyword),
      var1Name(var1Name), var1Value(var1Value),
      var2Name(var2Name), var2Value(var2Value) {}

bool POSTVariablesTest::run() {
    std::string boundary = "-------------------------" + std::to_string(std::time(nullptr));
    std::string body = "--" + boundary + "\r\n";
    body += "Content-Disposition: form-data; name=\"" + var1Name + "\"\r\n\r\n";
    body += var1Value + "\r\n";
    body += "--" + boundary + "\r\n";
    body += "Content-Disposition: form-data; name=\"" + var2Name + "\"\r\n\r\n";
    body += var2Value + "\r\n";
    body += "--" + boundary + "--\r\n";

    std::cout << "Sending POST request with variables to " << server << ":" << port << path << std::endl;

    actualResponse = sendMultipartPostRequest(server, port, path, "", body, "multipart/form-data; boundary=" + boundary);
    
    bool statusCodeMatch = actualResponse.find(expectedStatusCode) != std::string::npos;
    bool keywordMatch = actualResponse.find(expectedKeyword) != std::string::npos;

    std::cout << "Status code match: " << (statusCodeMatch ? "Yes" : "No") << std::endl;
    std::cout << "Keyword match: " << (keywordMatch ? "Yes" : "No") << std::endl;


    if (!statusCodeMatch || !keywordMatch) {
        std::cout << "Test failed. You can try the following curl command to debug:\n";
        std::cout << "curl -i -X POST -H \"Content-Type: multipart/form-data\" "
                  << "-F \"" << var1Name << "=" << var1Value << "\" "
                  << "-F \"" << var2Name << "=" << var2Value << "\" "
                  << "http://" << server << ":" << port << path << std::endl;
    }

    return statusCodeMatch && keywordMatch;
}

std::string POSTVariablesTest::getName() const {
    return "POST Variables Test";
}

CurlPOSTVariablesTest::CurlPOSTVariablesTest(const std::string& server, int port, const std::string& path, 
                                             const std::string& expectedStatusCode, const std::string& expectedKeyword,
                                             const std::string& var1Name, const std::string& var1Value,
                                             const std::string& var2Name, const std::string& var2Value)
    : Test(server, port, path, expectedStatusCode, expectedKeyword),
      var1Name(var1Name), var1Value(var1Value),
      var2Name(var2Name), var2Value(var2Value) {}

bool CurlPOSTVariablesTest::run() {
    std::string command = "curl -i -X POST -H \"Content-Type: multipart/form-data\" "
                          "-F \"" + var1Name + "=" + var1Value + "\" "
                          "-F \"" + var2Name + "=" + var2Value + "\" "
                          "http://" + server + ":" + std::to_string(port) + path;
    
    actualResponse = executeCurlCommand(command);

    bool statusCodeMatch = actualResponse.find(expectedStatusCode) != std::string::npos;
    bool keywordMatch = actualResponse.find(expectedKeyword) != std::string::npos;
    return statusCodeMatch && keywordMatch;
}

std::string CurlPOSTVariablesTest::getName() const {
    return "Curl POST Variables Test";
}

std::string readFileContent(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return "";
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}


void addPOSTTests(TestRunner& runner) {
    // Texto plano
    std::string textContent = readFileContent("texto.txt");
    if (!textContent.empty()) {
        runner.addTest(new POSTTest(SERVER_ADDRESS, 8080, "/upload", "200 OK", "File uploaded successfully", "texto.txt", textContent));
        runner.addTest(new CurlPOSTTest(SERVER_ADDRESS, 8080, "/upload", "200 OK", "File uploaded successfully", "texto.txt", textContent));
    }


    // Imagen JPG
    std::string jpgContent = readFileContent("foto.jpg");
    if (!jpgContent.empty()) {
        runner.addTest(new POSTTest(SERVER_ADDRESS, 8080, "/upload", "200 OK", "File uploaded successfully", "foto.jpg", jpgContent));
        runner.addTest(new CurlPOSTTest(SERVER_ADDRESS, 8080, "/upload", "200 OK", "File uploaded successfully", "foto.jpg", jpgContent));
    }




    // Video MP4 - demasiado grande
    std::string mp4Content = readFileContent("84mb.mp4");
    if (!jpgContent.empty()) {
        runner.addTest(new POSTTest(SERVER_ADDRESS, 8080, "/upload", "413", "Payload Too Large", "84mb.mp4", mp4Content));
        runner.addTest(new CurlPOSTTest(SERVER_ADDRESS, 8080, "/upload", "413", "Payload Too Large", "84mb.mp4", mp4Content));
    }

    // Nuevos tests para variables POST
    // calculadora
    runner.addTest(new POSTVariablesTest(SERVER_ADDRESS, 8080, "/cgi-bin/Python/calculadora.py", "200 OK", "90", 
                                         "num1", "30", "num2", "60"));
    runner.addTest(new CurlPOSTVariablesTest(SERVER_ADDRESS, 8080, "/cgi-bin/Python/calculadora.py", "200 OK", "90", 
                                        "num1", "30", "num2", "60"));  

}