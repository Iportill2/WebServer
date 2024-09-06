#ifndef TESTER2_HPP
#define TESTER2_HPP

#include <string>
#include <vector>
#include <chrono>

const std::string SERVER_ADDRESS = "127.0.0.1";
const int TIMEOUT_GET = 2;
const int TIMEOUT_POST = 1;
const int TIMEOUT_DELETE = 1;

class Timer {
private:
    std::chrono::high_resolution_clock::time_point start;

public:
    Timer() : start(std::chrono::high_resolution_clock::now()) {}
    
    long long elapsed() const {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
    }
};

class Test {
protected:
    std::string server;
    int port;
    std::string path;
    std::string expectedStatusCode;
    std::string expectedKeyword;
    std::string actualResponse;

public:
    Test(const std::string& server, int port, const std::string& path, 
         const std::string& expectedStatusCode, const std::string& expectedKeyword)
        : server(server), port(port), path(path), 
          expectedStatusCode(expectedStatusCode), expectedKeyword(expectedKeyword) {}


    std::string getServer() const { return server; }
    int getPort() const { return port; }
    std::string getPath() const { return path; }

    virtual bool run() = 0;
    virtual std::string getName() const = 0;
    virtual std::string getExpectedResult() const {
        return "Status Code: " + expectedStatusCode + ", Keyword: " + expectedKeyword;
    }
    virtual std::string getActualResponse() const {
        return actualResponse;
    }
    virtual ~Test() {}
};

class TestRunner {
public:
    TestRunner();
    void addTest(Test* test);
    void runAllTests(std::string method);
    void clearLogFile();

private:
    std::vector<Test*> tests;
    static const std::string LOG_FILE;
};

// Declaraciones de funciones auxiliares
std::string sendGETRequest(const std::string& host, int port, const std::string& path);
std::string sendMultipartPostRequest(const std::string& host, int port, const std::string& path, 
                                     const std::string& filename, const std::string& fileContent, 
                                     const std::string& contentType);
std::string sendDELETERequest(const std::string& host, int port, const std::string& path);
std::string executeCurlCommand(const std::string& command);

#endif // TESTER2_HPP