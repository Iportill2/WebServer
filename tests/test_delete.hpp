#ifndef TEST_DELETE_HPP
#define TEST_DELETE_HPP

#include "tester2.hpp"

class DELETETest : public Test {
public:
    DELETETest(const std::string& server, int port, const std::string& path,
               const std::string& expectedStatusCode, const std::string& expectedKeyword);
    bool run() override;
    std::string getName() const override;
};

class CurlDELETETest : public Test {
public:
    CurlDELETETest(const std::string& server, int port, const std::string& path,
                   const std::string& expectedStatusCode, const std::string& expectedKeyword);
    bool run() override;
    std::string getName() const override;
};

void addDELETETests(TestRunner& runner);

#endif // TEST_DELETE_HPP