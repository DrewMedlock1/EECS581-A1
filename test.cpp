/************************************************************************************
 *
 * Test cases for Assignment
 * Author: Drew Medlock
 * KUID: 3152931
 * File Created: 9/1/2026
 * File Description: Testing file containing test cases, as well as code for executing tests.
 *
 ***********************************************************************************/
#include <string>
#include <vector>

#include "main.h"

static std::vector<std::string> testFailureStrings;
static int testFailureCounter = 0;

struct testCase {
    std::string testString;
    unsigned long expectedOutAddress;
    int expectedOutPort;
    bool expectedReturn;
};


/* Test Cases are listed as structs inside this function */
std::vector<testCase> createTestList() {
    std::vector<testCase> testList;
    testList.push_back(testCase{"192.168.1.1", 3232235777, -1, true});
    testList.push_back(testCase{"10.0.0.255:8080end", 167772415, 8080, true});
    testList.push_back(testCase{"192a168.1.1.1", 2818638081, -1, true});
    testList.push_back(testCase{"192.168.1.1.", 0, -1, false});
    testList.push_back(testCase{"Connection from 192.168.1.1 refused", 3232235777, -1, true});
    testList.push_back(testCase{});
    testList.push_back(testCase{});
    return testList;
}

/*
 * This function is made by me, so it can be higher trust to verify the correctness of the extractIPv4 function.
 */
bool testExtractIPv4(const std::string& str, const unsigned long& expectedOutAddress, const int & expectedOutPort, bool expectedReturn) {
    unsigned long experimentalOutAddress = 0;
    int experimentalOutPort = 0;
    extractIPv4(str, experimentalOutAddress, experimentalOutPort);
    if (expectedOutAddress == experimentalOutAddress && expectedOutPort == experimentalOutPort) {
        return true;
    }
    else {
        testFailureStrings.push_back(str);
        testFailureCounter++;
        return false;
    }

}

int main() {
    auto testCases = createTestList();
    for (auto testCase : testCases) {

    }
}

