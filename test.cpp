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

/* Test Cases:
 * *
 *
 */


/*
 * This function is made by me, so it can be higher trust to verify the correctness of the extractIPv4 function.
 */
bool testExtractIPv4(const std::string& str, const unsigned long& expectedOutAddress, const int & expectedOutPort) {
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

