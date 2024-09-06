#ifndef TEST_POST_HPP
#define TEST_POST_HPP

#include "tester2.hpp"
#include <string>

class POSTTest : public Test {
private:
    std::string filename;
    std::string fileContent;
public:
    POSTTest(const std::string& server, int port, const std::string& path,
             const std::string& expectedStatusCode, const std::string& expectedKeyword,
             const std::string& filename, const std::string& fileContent);
    bool run() override;
    std::string getName() const override;
};

class CurlPOSTTest : public Test {
private:
    std::string filename;
    std::string fileContent;
public:
    CurlPOSTTest(const std::string& server, int port, const std::string& path,
                 const std::string& expectedStatusCode, const std::string& expectedKeyword,
                 const std::string& filename, const std::string& fileContent);
    bool run() override;
    std::string getName() const override;
};

class POSTVariablesTest : public Test {
private:
    std::string var1Name;
    std::string var1Value;
    std::string var2Name;
    std::string var2Value;
public:
    POSTVariablesTest(const std::string& server, int port, const std::string& path,
                      const std::string& expectedStatusCode, const std::string& expectedKeyword,
                      const std::string& var1Name, const std::string& var1Value,
                      const std::string& var2Name, const std::string& var2Value);
    bool run() override;
    std::string getName() const override;
};

class CurlPOSTVariablesTest : public Test {
private:
    std::string var1Name;
    std::string var1Value;
    std::string var2Name;
    std::string var2Value;
public:
    CurlPOSTVariablesTest(const std::string& server, int port, const std::string& path,
                          const std::string& expectedStatusCode, const std::string& expectedKeyword,
                          const std::string& var1Name, const std::string& var1Value,
                          const std::string& var2Name, const std::string& var2Value);
    bool run() override;
    std::string getName() const override;
};

void addPOSTTests(TestRunner& runner);

#endif // TEST_POST_HPP