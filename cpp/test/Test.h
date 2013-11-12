#ifndef TEST_H
#define TEST_H
/**
 * The unit test framework.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <map>
#include <vector>
#include <string>

class Test {
public:
    Test();
    virtual ~Test();
    static void add(std::string testSuiteName,
                    std::string testCaseName,
                    void (*testFunction)());
    static void test();
    static bool positive(const bool value);
    static bool negative(const bool value);

private:
    static bool _passed;
    static std::map< std::string, std::vector< std::pair<std::string, void (*)()> > > _tests;
};

#endif // TEST_H
