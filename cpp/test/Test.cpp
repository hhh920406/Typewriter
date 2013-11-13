#include <iomanip>
#include <iostream>
#include "Test.h"
using namespace std;

#ifdef SYS_WIN
#include <windows.h>
#endif

inline ostream& red(ostream &out) {
    #ifdef SYS_WIN
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 4);
    #endif
    #ifdef SYS_LINUX
    out << "\033[31m";
    #endif
    return out;
}

inline ostream& green(ostream &out) {
    #ifdef SYS_WIN
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 2);
    #endif
    #ifdef SYS_LINUX
    out << "\033[32m";
    #endif
    return out;
}

inline ostream& yellow(ostream &out) {
    #ifdef SYS_WIN
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 6);
    #endif
    #ifdef SYS_LINUX
    out << "\033[33m";
    #endif
    return out;
}

inline ostream& white(ostream &out) {
    #ifdef SYS_WIN
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 7);
    #endif
    #ifdef SYS_LINUX
    out << "\033[0m";
    #endif
    return out;
}

bool Test::_passed;
std::map< std::string, std::vector< std::pair<std::string, void (*)()> > > Test::_tests;

Test::Test() {
}

Test::~Test() {
}

void Test::add(std::string testSuiteName,
               std::string testCaseName,
               void (*testFunction)()) {
    if (Test::_tests.find(testSuiteName) == Test::_tests.end()) {
        vector< pair< string, void (*)()> > v;
        Test::_tests[testSuiteName] = v;
    }
    Test::_tests[testSuiteName].push_back(make_pair(testCaseName, testFunction));
}

void Test::test() {
    cout << yellow << "ZHG Unit Test" << endl << endl;

    int totalPassed = 0;
    int totalNumber = 0;
    for (map< string, vector< pair<string, void (*)()> > >::iterator suite = Test::_tests.begin(); suite != Test::_tests.end(); ++suite) {
        int casePassed = 0;
        int caseNumber = 0;
        string testSuiteName = suite->first;
        for (vector< pair<string, void (*)()> >::iterator testCase = suite->second.begin(); testCase != suite->second.end(); ++testCase) {
            string testCaseName = testCase->first;
            Test::_passed = true;
            try {
                testCase->second();
            } catch (...) {
                Test::_passed = false;
            }
            ++caseNumber;
            ++totalNumber;
            if (Test::_passed) {
                ++casePassed;
                ++totalPassed;
                cout << green << "[ PASSED ]";
                cout << white << " " << testSuiteName << " : " << testCaseName << endl;
            } else {
                cout << red << "[ FAILED ]";
                cout << white <<  " " << testSuiteName << " : " << testCaseName << endl;
            }
        }
        if (casePassed == caseNumber) {
            cout << green << "[  100%  ]";
            cout << white << " " << testSuiteName <<endl;
        } else {
            int radio = 100 * casePassed / caseNumber;
            cout << red << "[  " << setw(3) << radio << "%  ]";
            cout << white << " " << testSuiteName <<endl;
        }
        cout << endl;
    }
    if (totalPassed == totalNumber) {
        cout << green << "[  100%  ]";
        cout << white << " Total" <<endl;
    } else {
        int radio = 100 * totalPassed / totalNumber;
        cout << red << "[  " << setw(3) << radio << "%  ]";
        cout << white << " Total" <<endl;
    }

    cout << white << endl;
}

void Test::fail() {
    Test::_passed = false;
}
