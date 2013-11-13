#ifndef TEST_H
#define TEST_H
/**
 * The unit test framework.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <map>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

class Test {
public:
    Test();
    virtual ~Test();
    static void add(std::string testSuiteName,
                    std::string testCaseName,
                    void (*testFunction)());
    static void test();
    static void fail();

private:
    static bool _passed;
    static std::map< std::string, std::vector< std::pair<std::string, void (*)()> > > _tests;
};

std::ostream& red(std::ostream &out);
std::ostream& green(std::ostream &out);
std::ostream& yellow(std::ostream &out);
std::ostream& white(std::ostream &out);

template<typename T>
bool TEST_EQUAL(const T &a, const T &b) {
    if (!(a == b)) {
        Test::fail();
        std::cout << white << "Equal: " << std::endl;
        std::cout << a << std::endl;
        std::cout << b << std::endl;
        return true;
    }
    return false;
}

template<typename T>
bool TEST_UNEQUAL(const T &a, const T &b) {
    if (a == b) {
        Test::fail();
        std::cout << white << "Unequal: " << std::endl;
        std::cout << a << std::endl;
        std::cout << b << std::endl;
        return true;
    }
    return false;
}

template<typename T>
bool TEST_AEQUAL(const T &a, const T &b) {
    if (fabs(a - b) > 1e-8) {
        Test::fail();
        std::cout << white << "Approximate equal: " << std::endl;
        std::cout << a << std::endl;
        std::cout << b << std::endl;
        return true;
    }
    return false;
}

#endif // TEST_H
