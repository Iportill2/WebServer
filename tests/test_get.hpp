#ifndef TEST_GET_HPP
#define TEST_GET_HPP

#include "tester2.hpp"

class GETTest : public Test {
public:
    GETTest(const std::string& server, int port, const std::string& path, 
            const std::string& expectedStatusCode, const std::string& expectedKeyword);
    bool run() override;
    std::string getName() const override;
};

class CurlGETTest : public Test {
public:
    CurlGETTest(const std::string& server, int port, const std::string& path, 
                const std::string& expectedStatusCode, const std::string& expectedKeyword);
    bool run() override;
    std::string getName() const override;
};

void addGETTests(TestRunner& runner);

#endif // TEST_GET_HPP