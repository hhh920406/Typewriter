#include <ctime>
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
    time_t testStart = clock();
    for (map< string, vector< pair<string, void (*)()> > >::iterator suite = Test::_tests.begin(); suite != Test::_tests.end(); ++suite) {
        int casePassed = 0;
        int caseNumber = 0;
        string testSuiteName = suite->first;
        time_t suiteStart = clock();
        for (vector< pair<string, void (*)()> >::iterator testCase = suite->second.begin(); testCase != suite->second.end(); ++testCase) {
            string testCaseName = testCase->first;
            Test::_passed = true;
            time_t caseStart = clock();
            try {
                testCase->second();
            } catch (...) {
                Test::_passed = false;
            }
            time_t caseFinish = clock();
            ++caseNumber;
            ++totalNumber;
            if (Test::_passed) {
                ++casePassed;
                ++totalPassed;
                cout << green << "[ PASSED ]";
            } else {
                cout << red << "[ FAILED ]";
            }
            int time = (int)((caseFinish - caseStart) * 1000.0 / CLOCKS_PER_SEC);
            cout << white << setw(5) << time << " ms ";
            cout << testSuiteName << " : " << testCaseName << endl;
        }
        time_t suiteFinish = clock();
        if (casePassed == caseNumber) {
            cout << green << "[  100%  ]";
        } else {
            int radio = 100 * casePassed / caseNumber;
            cout << red << "[  " << setw(3) << radio << "%  ]";
        }
        int time = (int)((suiteFinish - suiteStart) * 1000.0 / CLOCKS_PER_SEC);
        cout << white << setw(5) << time << " ms " << testSuiteName <<endl;
        cout << endl;
    }
    time_t testFinish = clock();
    if (totalPassed == totalNumber) {
        cout << green << "[  100%  ]";
    } else {
        int radio = 100 * totalPassed / totalNumber;
        cout << red << "[  " << setw(3) << radio << "%  ]";
    }
    int time = (int)((testFinish - testStart) * 1000.0 / CLOCKS_PER_SEC);
    cout << white << setw(5) << time << " ms Total" <<endl;

    cout << white << endl;
}

void Test::fail() {
    Test::_passed = false;
}
