#include "test_delete.hpp"
#include "tester2.hpp"
#include <iostream>

DELETETest::DELETETest(const std::string& server, int port, const std::string& path,
                       const std::string& expectedStatusCode, const std::string& expectedKeyword)
    : Test(server, port, path, expectedStatusCode, expectedKeyword) {}

bool DELETETest::run() {
//    std::cout << "Sending DELETE request to " << server << ":" << port << path << std::endl;
    std::string response = sendDELETERequest(server, port, path);
    
    if (response.find("Error") == 0 || response.find("Connection timeout") == 0) {
        std::cout << "DELETE request failed: " << response << std::endl;
        return false;
    }

    bool statusCodeMatch = response.find(expectedStatusCode) != std::string::npos;


    std::cout << "Status code match: " << (statusCodeMatch ?  "Yes" : "No") << std::endl;


    if (!statusCodeMatch) {
        std::cout << "Test failed. Response received:\n" << response << std::endl;
        std::cout << "You can try the following curl command to debug:\n";
        std::cout << "curl -X DELETE http://" << server << ":" << port << path << std::endl;
    }

    return statusCodeMatch ;
}

std::string DELETETest::getName() const {
    return "DELETE Test";
}

CurlDELETETest::CurlDELETETest(const std::string& server, int port, const std::string& path,
                               const std::string& expectedStatusCode, const std::string& expectedKeyword)
    : Test(server, port, path, expectedStatusCode, expectedKeyword) {}

bool CurlDELETETest::run() {

    // Ahora intentamos eliminar el archivo
//    std::cout << "Sending DELETE request to " << server << ":" << port << path << std::endl;
    std::string command = "curl -I -X DELETE http://" + server + ":" + std::to_string(port) + path;
    std::string response = executeCurlCommand(command);
    
    bool statusCodeMatch = response.find(expectedStatusCode) != std::string::npos;

    std::cout << "Status code match: " << (statusCodeMatch ? "Yes" : "No") << std::endl;

    if (!statusCodeMatch) {
        std::cout << "Test failed. You can try the following curl command to debug:\n";
        std::cout << command << std::endl;
    }

    return statusCodeMatch ;
}

std::string CurlDELETETest::getName() const {
    return "Curl DELETE Test";
}

void addDELETETests(TestRunner& runner) {
    runner.addTest(new DELETETest(SERVER_ADDRESS, 8080, "/files/texto.txt", "204", ""));
    runner.addTest(new CurlDELETETest(SERVER_ADDRESS, 8080, "/files/foto.jpg", "204", ""));
}