#include "tester2.hpp"
#include "test_get.hpp"
#include "test_post.hpp"
#include "test_delete.hpp"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <cstring>
#include <cerrno>
#include <sys/select.h>
#include <sys/stat.h>
#include <iomanip> 


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

const std::string TestRunner::LOG_FILE = "fail_log.txt";

static std::string ResultadoGET;
static std::string ResultadoPOST;
static std::string ResultadoDELETE;
static std::stringstream GeneralOutput;
static std::stringstream GeneralFinish;

TestRunner::TestRunner() {
    std::remove(LOG_FILE.c_str()); // Delete the log file
    clearLogFile();
}

void TestRunner::clearLogFile() {
    std::ofstream ofs(LOG_FILE, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void TestRunner::addTest(Test* test) {
    tests.push_back(test);

}


// Función para calcular la longitud real de una cadena con códigos de escape
int visibleLength(const std::string& str) {
    int length = 0;
    bool inEscapeSequence = false;

    for (char ch : str) {
        if (ch == '\033') {  // Detecta el inicio de una secuencia de escape
            inEscapeSequence = true;
        }
        else if (inEscapeSequence && ch == 'm') {  // Detecta el final de una secuencia de escape
            inEscapeSequence = false;
        }
        else if (!inEscapeSequence) {
            ++length;
        }
    }
    return length;
}

// Función para formatear una línea con un ancho máximo y la última palabra alineada a la derecha
std::string formatLineWithRightAlignedWord(const std::string& line, int width) {
    // Encuentra la posición de la última palabra
    size_t lastSpace = line.find_last_of(' ');
    std::string lastWord = line.substr(lastSpace + 1);
    std::string text = line.substr(0, lastSpace);

    int visibleLastWordLength = visibleLength(lastWord);
    int availableSpace = width - visibleLastWordLength;

    std::stringstream ss;
    ss << std::left << std::setw(availableSpace) << std::setfill(' ') << text << lastWord;
    return ss.str();
}

// Función que procesa todo el texto, aplicando el formato línea por línea
std::string formatAllLines(const std::string& text, int width) {
    std::istringstream stream(text);
    std::string line;
    std::ostringstream formattedText;

    while (std::getline(stream, line)) {
        formattedText << formatLineWithRightAlignedWord(line, width) << "\n";
    }

    return formattedText.str();
}

std::string formatLineWithRightAlignedWordResult(const std::string& line, int width) {
    // Encuentra la posición de la última palabra
    size_t lastSpace = line.find_last_of("\033[");
    std::string lastWord = line.substr(lastSpace + 1);
    std::string text = line.substr(0, lastSpace);

    int visibleLastWordLength = visibleLength(lastWord);
    int availableSpace = width - visibleLastWordLength;

    std::stringstream ss;
    ss << std::left << std::setw(availableSpace) << std::setfill(' ') << text << lastWord << RESET;
    return ss.str();
}

std::string formatAllLinesResults(const std::string& text, int width) {
    std::istringstream stream(text);
    std::string line;
    std::ostringstream formattedText;

    while (std::getline(stream, line)) {
        formattedText << formatLineWithRightAlignedWordResult(line, width) << "\n";
    }

    return formattedText.str();
}




void TestRunner::runAllTests(std::string this_method) {
    int passed = 0;
    int testNumber = 1;
    std::stringstream this_test;
    for (auto test : tests) {

        GeneralOutput.str("");
        GeneralOutput.clear();  // Resetea los flags del stream
        GeneralOutput << "\n";

        GeneralOutput << "Test " << testNumber << ": " << test->getName() << "... ";
        Timer timer;
        bool result = test->run();
        long long elapsed = timer.elapsed();
        
        if (result) {
           GeneralOutput << GREEN << "PASSED" << RESET;
            passed++;
        } else {
            GeneralOutput << RED << "FAILED" << RESET;
            // Log failure details
            std::ofstream log(LOG_FILE, std::ios_base::app);
            if (log.is_open()) {
                log << "Test " << testNumber << ": " << test->getName() << " FAILED\n";
                log << "Expected: " << test->getExpectedResult() << "\n";
                log << "Actual response (first 1500 chars):\n" << test->getActualResponse().substr(0, 1500) << "\n";
                
                // Add curl command for CurlGETTest
                if (dynamic_cast<CurlGETTest*>(test) != nullptr) {
                    CurlGETTest* curlTest = dynamic_cast<CurlGETTest*>(test);
                    log << "Curl command to reproduce:\n";
                    log << "curl -i -X GET 'http://" << curlTest->getServer() << ":" << curlTest->getPort() << curlTest->getPath() << "'\n";
                }
                
                log << "\n";
            }
        }
        GeneralOutput << " (Time: " << elapsed << "ms)" << std::endl << std::endl;
//        std::cout << GeneralOutput.str();
    std::string formattedOutput = formatAllLines(GeneralOutput.str(), 80);
    std::cout << formattedOutput;


        testNumber++;
    }
/*     GeneralOutput << "\nMethod " << this_method << 
    "Total tests: " << tests.size() << ", Passed: " << GREEN << passed << RESET 
              << ", Failed: " << RED << (tests.size() - passed) << RESET << std::endl; */
    GeneralFinish << "\nMethod:" << this_method << 
    "-> Total tests: " << tests.size() << ", Passed: " << GREEN << passed << RESET 
              << ", Failed: " << RED << (tests.size() - passed) << RESET << std::endl;

    this_test << "\nMethod:" << this_method << 
    "-> Total tests: " << tests.size() << ", Passed: " << GREEN << passed << RESET 
              << ", Failed: " << RED << (tests.size() - passed) << RESET << std::endl;
   std::cout << this_test.str();


}



std::string sendMultipartPostRequest(const std::string& host, int port, const std::string& path, 
                                     const std::string& filename, const std::string& body, 
                                     const std::string& contentType) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        return "Error creating socket: " + std::string(strerror(errno));
    }
    (void) filename;
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, host.c_str(), &server_addr.sin_addr) <= 0) {
        close(sock);
        return "Invalid address/ Address not supported";
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        close(sock);
        return "Connection Failed: " + std::string(strerror(errno));
    }

    std::string request = "POST " + path + " HTTP/1.1\r\n";
    request += "Host: " + host + "\r\n";
    request += "Content-Type: " + contentType + "\r\n";
    request += "Content-Length: " + std::to_string(body.length()) + "\r\n";
    request += "\r\n" + body;

    if (send(sock, request.c_str(), request.length(), 0) < 0) {
        close(sock);
        return "Send failed: " + std::string(strerror(errno));
    }

    std::string response;
    char buffer[4096];
    int bytes_received;
    struct timeval tv;
    tv.tv_sec = TIMEOUT_POST;  
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    while ((bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        response += buffer;
    }

    if (bytes_received < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            close(sock);
            return "Receive timeout. Partial response:\n" + response;
        } else {
            close(sock);
            return "Receive failed: " + std::string(strerror(errno));
        }
    }

    close(sock);
    return response;
}


std::string sendGETRequest(const std::string& host, int port, const std::string& path) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        return "Error creating socket: " + std::string(strerror(errno));
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, host.c_str(), &server_addr.sin_addr) <= 0) {
        close(sock);
        return "Invalid address/ Address not supported";
    }

    // Set non-blocking
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);

    // Attempting to connect with timeout
    int res = connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (res < 0) {
        if (errno == EINPROGRESS) {
            fd_set fdset;
            struct timeval tv;
            FD_ZERO(&fdset);
            FD_SET(sock, &fdset);
            tv.tv_sec = TIMEOUT_GET;  // 5 seconds timeout
            tv.tv_usec = 0;

            if (select(sock + 1, NULL, &fdset, NULL, &tv) == 1) {
                int so_error;
                socklen_t len = sizeof so_error;
                getsockopt(sock, SOL_SOCKET, SO_ERROR, &so_error, &len);
                if (so_error != 0) {
                    close(sock);
                    return "Connection error: " + std::string(strerror(so_error));
                }
            } else {
                close(sock);
                return "Connection timeout";
            }
        } else {
            close(sock);
            return "Connection error: " + std::string(strerror(errno));
        }
    }

    // Set back to blocking mode
    fcntl(sock, F_SETFL, flags);

    std::string request = "GET " + path + " HTTP/1.1\r\n";
    request += "Host: " + host + "\r\n";
    request += "Connection: close\r\n\r\n";

    if (send(sock, request.c_str(), request.length(), 0) < 0) {
        close(sock);
        return "Send failed: " + std::string(strerror(errno));
    }

    std::string response;
    char buffer[4096];
    struct timeval tv;
    tv.tv_sec = TIMEOUT_GET;  // 5 seconds timeout
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    int bytes_received;
    while ((bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        response += buffer;
    }

    if (bytes_received < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            close(sock);
            return "Receive timeout. Partial response:\n" + response;
        } else {
            close(sock);
            return "Receive failed: " + std::string(strerror(errno));
        }
    }

    close(sock);
    return response;
}

std::string sendDELETERequest(const std::string& host, int port, const std::string& path) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        return "Error creating socket: " + std::string(strerror(errno));
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, host.c_str(), &server_addr.sin_addr) <= 0) {
        close(sock);
        return "Invalid address/ Address not supported: " + std::string(strerror(errno));
    }

    // Set non-blocking
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);

    // Trying to connect with timeout
    int res = connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (res < 0) {
        if (errno == EINPROGRESS) {
            fd_set fdset;
            struct timeval tv;
            FD_ZERO(&fdset);
            FD_SET(sock, &fdset);
            tv.tv_sec = TIMEOUT_DELETE;  
            tv.tv_usec = 0;

            if (select(sock + 1, NULL, &fdset, NULL, &tv) == 1) {
                int so_error;
                socklen_t len = sizeof so_error;
                getsockopt(sock, SOL_SOCKET, SO_ERROR, &so_error, &len);
                if (so_error != 0) {
                    close(sock);
                    return "Connection error: " + std::string(strerror(so_error));
                }
            } else {
                close(sock);
                return "Connection timeout";
            }
        } else {
            close(sock);
            return "Connection error: " + std::string(strerror(errno));
        }
    }

    // Set back to blocking mode
    fcntl(sock, F_SETFL, flags);

    std::string request = "DELETE " + path + " HTTP/1.1\r\n";
    request += "Host: " + host + "\r\n";
    request += "Connection: close\r\n\r\n";

    if (send(sock, request.c_str(), request.length(), 0) < 0) {
        close(sock);
        return "Send failed: " + std::string(strerror(errno));
    }

    std::string response;
    char buffer[4096];
    struct timeval tv;
    tv.tv_sec = TIMEOUT_DELETE; 
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    int bytes_received;
    while ((bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        response += buffer;
    }

    if (bytes_received < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            close(sock);
            return "Receive timeout. Partial response:\n" + response;
        } else {
            close(sock);
            return "Receive failed: " + std::string(strerror(errno));
        }
    }

    close(sock);
    return response;
}

std::string executeCurlCommand(const std::string& command) {
    std::string result;
    char buffer[128];
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "popen() failed!";
    }
    while (fgets(buffer, sizeof buffer, pipe) != NULL) {
        result += buffer;
    }
    pclose(pipe);
    return result;
}

void copyFile(const std::string& source, const std::string& destination) {
    std::ifstream src(source, std::ios::binary);
    std::ofstream dst(destination, std::ios::binary);

    if (!src.is_open()) {
        std::cerr << "Error opening source file: " << source << " - " << strerror(errno) << std::endl;
        return;
    }

    if (!dst.is_open()) {
        std::cerr << "Error opening destination file: " << destination << " - " << strerror(errno) << std::endl;
        return;
    }

    dst << src.rdbuf();

    if (src.fail()) {
        std::cerr << "Error reading source file: " << source << " - " << strerror(errno) << std::endl;
    }

    if (dst.fail()) {
        std::cerr << "Error writing to destination file: " << destination << " - " << strerror(errno) << std::endl;
    }
}

void copyAssetsFiles() {
    std::string assetsPath = "assets/";
    std::vector<std::string> filesToCopy = {"texto.txt", "foto.jpg", "84mb.mp4"};

    for (const auto& file : filesToCopy) {
        std::string sourcePath = assetsPath + file;
        std::string destPath = file;

        struct stat buffer;
        if (stat(sourcePath.c_str(), &buffer) == 0) {
            copyFile(sourcePath, destPath);
            std::cout << "Copied " << file << " from assets to current directory." << std::endl;
        } else {
            std::cerr << "Error: " << file << " not found in assets directory." << std::endl;
        }
    }
} 

bool fileExists(const std::string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

int main() {

    copyAssetsFiles();
    
    std::stringstream output;
    bool fileExistsOnServer;
    bool serverFilePathText;
    bool mp4upload;
    
    TestRunner runner;
    addGETTests(runner);
    runner.runAllTests(" Get ");

    TestRunner runner2;
    addPOSTTests(runner2);
    runner2.runAllTests(" Post ");

    output  << GREEN "\nCheck if files where uploaded: " << RESET << "\n";

    std::string serverFilePathJpg = "../www/examen/files/foto.jpg";
    fileExistsOnServer = fileExists(serverFilePathJpg);
    output << "File exists foto.jpg on server: " << (fileExistsOnServer ? GREEN "Yes" RESET : RED "No" RESET) << "\n";

    std::string serverFilePath = "../www/examen/files/texto.txt";
    serverFilePathText = fileExists(serverFilePath);
    output << "File exists texto.text on server: " << (serverFilePathText ? GREEN "Yes" RESET : RED "No" RESET) << "\n" ;

    std::string mp4path = "../www/examen/files/84mb.mp4";
    mp4upload = fileExists(mp4path);
    output << "File exists 80mb.mp4 on server: " << (mp4upload ? RED "Yes" RESET : GREEN "No" RESET) << "\n";


    output << "\n";



    TestRunner runner3;
    addDELETETests(runner3);
    runner3.runAllTests(" Delete ");

    output << GREEN "Check if files where deleted: " << RESET << "\n";
    fileExistsOnServer = fileExists(serverFilePathJpg);
    output << "File exists foto.jpg on server: " << (fileExistsOnServer ? RED "Yes" RESET : GREEN "No" RESET) << "\n";

    serverFilePathText = fileExists(serverFilePath);
    output << "File exists texto.text on server: " << (serverFilePathText ? RED "Yes" RESET : GREEN "No" RESET) << "\n\n" ;
    std::cout << std::endl <<  GREEN << "Complete Tested Results: " << RESET << std::endl;
    
    std::string formattedOutput;
    
    formattedOutput = formatAllLines(GeneralFinish.str(), 80);
    std::cout << GeneralFinish.str();

    formattedOutput = formatAllLines(output.str(), 80);
    std::cout << formattedOutput;
/* 
    std::string formattedOutput = formatAllLines(output.str(), 60);
    std::cout << formattedOutput; */

//    std::cout << output.str();
    return 0;
}