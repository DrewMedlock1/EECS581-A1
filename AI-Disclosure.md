# AI Disclosure Statement
***
*

***
# Prompts:
### 1. GPT-6 Astra, Thinking level: Max, Date: 9/15/2026
```
# Role
C++ Expert

# Goal
Complete the function given in the input according to requirements
and constraints. Can also include any helper functions necesary.

# Input
<INPUT>
Problem description
Write a C++ program that reads a line of text and extracts a single valid IPv4 address — optionally followed by a port number — embedded anywhere in that text. 
Only digits, periods (.), and colons (:) are ever part of a valid token; every other character is garbage and is skipped. A candidate token must match the address grammar in full — no partial matches, no truncating to find a valid piece inside a longer run.

An address is four octets separated by periods (octet.octet.octet.octet), each octet 1–3 digits, value 0–255, no leading 
zero unless the value is exactly 0. An optional :port may follow the fourth octet: 1–5 digits, value 0–65535, same leading-zero rule. If a colon is present, the port must be fully valid or the entire match — address included — is rejected.

Returns true if a valid address was found, false otherwise.
On success: outAddress holds the 32-bit value,
and outPort holds the port number, or -1 if no port was present.
On failure: outAddress is set to 0 and outPort is set to -1.

Function Declaration:
bool extractIPv4(const std::string& str, unsigned long& outAddress, int& outPort)
</INPUT>

# Requirements
- Exactly one valid address may be extracted per input line; everything else in the line is either garbage (skipped) or part of a candidate token that fails validation.
- Reject anything that does not exactly match the grammar above — wrong octet count, empty octet, out-of-range octet or port, a disallowed leading zero, a second colon, a colon not immediately after the fourth octet, or a stray period/colon directly adjacent to an otherwise-valid address.
- Requirement 3

# Constraints
- Do not use the following:
   - Any string-to-number conversion function: atoi, atol, atoll, strtol, strtoul, strtod, stoi, stol, stoul, sscanf, scanf with numeric conversions.
   - Any address-parsing library function: inet_aton, inet_pton, inet_addr, or equivalents.
   - Any regular-expression facility (std::regex, POSIX regex.h, or similar).

# Output Format
The output should match the given function declaration, written in C++. 
```
### Output: https://chatgpt.com/share/6aa9d9ca-91ec-83ea-b4d9-3d4507c3a64b
```
#include <cstddef>
#include <string>

bool extractIPv4(const std::string& str,
                 unsigned long& outAddress,
                 int& outPort)
{
    outAddress = 0;
    outPort = -1;

    const auto isDigit = [](char c) {
        return c >= '0' && c <= '9';
    };
    const auto isTokenChar = [&](char c) {
        return isDigit(c) || c == '.' || c == ':';
    };

    for (std::size_t i = 0; i < str.size();) {
        if (!isTokenChar(str[i])) {
            ++i;
            continue;
        }

        // Consume the entire candidate before validating any of it.
        const std::size_t begin = i;
        while (i < str.size() && isTokenChar(str[i]))
            ++i;
        const std::size_t end = i;
        std::size_t pos = begin;

        const auto readNumber = [&](std::size_t maxDigits,
                                    unsigned limit, unsigned& value) {
            const std::size_t start = pos;
            value = 0;

            while (pos < end && isDigit(str[pos])) {
                if (pos - start >= maxDigits)
                    return false;

                value = value * 10 +
                        static_cast<unsigned>(str[pos++] - '0');

                if (value > limit)
                    return false;
            }

            return pos > start &&
                   (pos - start == 1 || str[start] != '0');
        };

        unsigned long address = 0;
        bool valid = true;

        for (int part = 0; part < 4; ++part) {
            unsigned octet;
            if (!readNumber(3, 255, octet)) {
                valid = false;
                break;
            }

            // Pack the first octet into the most significant byte.
            address = (address << 8) | octet;

            if (part < 3) {
                if (pos == end || str[pos] != '.') {
                    valid = false;
                    break;
                }
                ++pos;
            }
        }

        if (!valid)
            continue;

        int port = -1;
        if (pos < end && str[pos] == ':') {
            ++pos;
            unsigned parsedPort;

            if (!readNumber(5, 65535, parsedPort))
                continue;

            port = static_cast<int>(parsedPort);
        }

        if (pos != end)
            continue;

        // Return the first valid complete token.
        outAddress = address;
        outPort = port;
        return true;
    }

    return false;
}
```
### 2. Google Gemini 3.8 Flash Extended, Date: 9/16/2026
```
I have these 3 files and it says that there is an undefined reference to extractIPv4 in test.cpp:

main.cpp:
/************************************************************************************
 *
 * Assignment 1
 * Author: Drew Medlock
 * KUID: 3152931
 * File Created: 9/1/2026
 * File Description: Main file that provides the extractIPv4 function and main loop.
 *
 ***********************************************************************************/
// These imports are from the standard library
#include <cstddef>
#include <string>
/*
 * This function has been generated by GPT-6 Astra
 * AI generated comments have been stripped out, and replaced with my understanding of the function.
 */
bool extractIPv4(const std::string& str, unsigned long& outAddress, int& outPort)
{
    // These set the default values of the 2 input values for returning if nothing matches.
    outAddress = 0;
    outPort = -1;

    const auto isDigit = [](char c) {
        return c >= '0' && c <= '9';
    };
    const auto isTokenChar = [&](char c) {
        return isDigit(c) || c == '.' || c == ':';
    };

    for (std::size_t i = 0; i < str.size();) {
        if (!isTokenChar(str[i])) {
            ++i;
            continue;
        }

        const std::size_t begin = i;
        while (i < str.size() && isTokenChar(str[i]))
            ++i;
        const std::size_t end = i;
        std::size_t pos = begin;

        const auto readNumber = [&](std::size_t maxDigits,
                                    unsigned limit, unsigned& value) {
            const std::size_t start = pos;
            value = 0;

            while (pos < end && isDigit(str[pos])) {
                if (pos - start >= maxDigits)
                    return false;

                value = value * 10 +
                        static_cast<unsigned>(str[pos++] - '0');

                if (value > limit)
                    return false;
            }

            return pos > start &&
                   (pos - start == 1 || str[start] != '0');
        };

        unsigned long address = 0;
        bool valid = true;

        for (int part = 0; part < 4; ++part) {
            unsigned octet;
            if (!readNumber(3, 255, octet)) {
                valid = false;
                break;
            }

            // Pack the first octet into the most significant byte.
            address = (address << 8) | octet;

            if (part < 3) {
                if (pos == end || str[pos] != '.') {
                    valid = false;
                    break;
                }
                ++pos;
            }
        }

        if (!valid)
            continue;

        int port = -1;
        if (pos < end && str[pos] == ':') {
            ++pos;
            unsigned parsedPort;

            if (!readNumber(5, 65535, parsedPort))
                continue;

            port = static_cast<int>(parsedPort);
        }

        if (pos != end)
            continue;

        // Return the first valid complete token.
        outAddress = address;
        outPort = port;
        return true;
    }

    return false;
}

int main() {
    return 0;
}

main.h
#ifndef MAIN
#define MAIN

bool extractIPv4(const std::string& str, unsigned long& outAddress, int& outPort);

#endif //MAIN

test.cpp:
/************************************************************************************
 *
 * Test cases for Assignment
 * Author: Drew Medlock
 * KUID: 3152931
 * File Created: 9/1/2026
 * File Description: Testing file containing test cases, as well as code for executing tests.
 *
 ***********************************************************************************/
#include <iostream>
#include <ostream>
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
    // Given test cases:
    testList.push_back(testCase{"192.168.1.1", 3232235777, -1, true});
    testList.push_back(testCase{"10.0.0.255:8080end", 167772415, 8080, true});
    testList.push_back(testCase{"192a168.1.1.1", 2818638081, -1, true});
    testList.push_back(testCase{"192.168.1.1.", 0, -1, false});
    testList.push_back(testCase{"Connection from 192.168.1.1 refused", 3232235777, -1, true});
    testList.push_back(testCase{"192.168.01.1", 0, -1, false});
    testList.push_back(testCase{"1.2.3.4:99999", 0, -1, false});
    testList.push_back(testCase{"12.34.56", 0, -1, false});
    testList.push_back(testCase{"no number here", 0, -1, false});
    // Custom test Cases;
    testList.push_back(testCase{"192.168.1.1:", 0, -1, false});
    testList.push_back(testCase{"256.168.1.1", 0, -1, false});
    testList.push_back(testCase{"255.255.255.255", 4294967295, -1, true});
    testList.push_back(testCase{"0.0.0.0", 0, -1, true});
    return testList;
}

/*
 * This function is made by me, so it can be higher trust to verify the correctness of the extractIPv4 function.
 */
bool testExtractIPv4(const std::string& str, const unsigned long& expectedOutAddress, const int & expectedOutPort, bool expectedReturn) {
    unsigned long experimentalOutAddress = 0;
    int experimentalOutPort = 0;
    bool experimentalReturn = extractIPv4(str, experimentalOutAddress, experimentalOutPort);
    if (expectedOutAddress == experimentalOutAddress && expectedOutPort == experimentalOutPort &&
        experimentalReturn == expectedReturn) {
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
    bool passedTests = true;
    for (auto testCase : testCases) {
        if (!testExtractIPv4(testCase.testString, testCase.expectedOutAddress, testCase.expectedOutPort, testCase.expectedReturn)) {
            passedTests = false;
        }
    }
    if (!passedTests) {
        std::cout  << testFailureCounter << " Tests failed." << std::endl;
        for (const auto& str : testFailureStrings) {
            std::cout << str << std::endl;
        }
    }
}
```
### Output:
```
This linker error occurs because **`test.cpp` was compiled without linking the compiled object code from `main.cpp**` (for example, running `g++ test.cpp -o test`). While `test.cpp` knows the function declaration via `main.h`, the linker cannot find the actual definition of `extractIPv4`.

However, simply running `g++ main.cpp test.cpp -o test` will trigger a secondary error: **`multiple definition of 'main'`**, because both `main.cpp` and `test.cpp` define an `int main()` function.

Here are the two ways to resolve this:

---

**Approach 1: Separate Logic from Entry Points (Standard Practice)**

The standard C++ project architecture isolates reusable functions from executable entry points.

1. **Move `extractIPv4` out of `main.cpp**` into a dedicated translation unit, e.g., `extractIPv4.cpp` and `extractIPv4.h`.
2. Keep `main.cpp` solely for your actual application program entry point.
3. Keep `test.cpp` solely for the test harness.

File structure:

* **`extractIPv4.h`**
```cpp
#ifndef EXTRACT_IPV4_H
#define EXTRACT_IPV4_H

#include <string>

bool extractIPv4(const std::string& str, unsigned long& outAddress, int& outPort);

#endif


*(Note: Always include `<string>` inside the header so it does not rely on whoever includes it.)*
* **`extractIPv4.cpp`**
```cpp
#include "extractIPv4.h"
#include <cstddef>

bool extractIPv4(const std::string& str, unsigned long& outAddress, int& outPort) {
    // ... implementation unchanged ...
}


* **Compilation commands:**
* To build the test suite:
```bash
g++ -std=c++17 extractIPv4.cpp test.cpp -o run_tests
./run_tests


* To build the main program:
bash
g++ -std=c++17 extractIPv4.cpp main.cpp -o app
./app

---

**Approach 2: Preprocessor Guard (If File Names Are Fixed by an Assignment)**

If your assignment rubric strictly forbids adding new files and requires `main.cpp`, `main.h`, and `test.cpp`, guard the `main()` function in `main.cpp` using a macro definition:

1. Wrap `main()` in `main.cpp`:
```cpp
#ifndef UNIT_TEST
int main() {
    return 0;
}
#endif


2. Compile both files together while defining `UNIT_TEST`:
g++ -std=c++17 -DUNIT_TEST main.cpp test.cpp -o run_tests
./run_tests


3. Add `#include <string>` to `main.h` to prevent compilation failures when `main.h` is included without `<string>` preceding it.
```
### 3. Google Gemini 3.8 Flash Extended, Date: 9/16/2026
```
How does the preprocessor guard help?
```
### Output:
```
The preprocessor guard prevents the linker error **`multiple definition of 'main'`** by selectively deleting `main()` from `main.cpp` before the compiler ever sees it.

Here is how the toolchain handles it step-by-step:

* **1. Flag injection (`-DUNIT_TEST`):** Passing `-DUNIT_TEST` to `g++` tells the compiler's preprocessor to treat the word `UNIT_TEST` as if `#define UNIT_TEST` were written at the very top of the file.
* **2. Preprocessing phase (`#ifndef`):** `#ifndef` stands for *"if not defined"*. When the preprocessor evaluates `main.cpp`, it checks if `UNIT_TEST` exists:
* Because `-DUNIT_TEST` defined it, the `#ifndef UNIT_TEST` condition evaluates to **false**.
* The preprocessor completely strips out the block of code inside it (`int main() { ... }`), replacing it with blank space.


* **3. Compilation phase:** The compiler translates the preprocessed code into machine instructions. At this point, `main.cpp` contains only the compiled code for `extractIPv4`—no entry point exists in this file.
* **4. Linking phase:** The linker combines the compiled object code from both `main.cpp` and `test.cpp`:
* It finds the definition of `extractIPv4` coming from `main.cpp`, resolving your original **undefined reference** error.
* It encounters exactly **one** `main()` function (from `test.cpp`), avoiding the symbol collision error that would normally occur if two files both declared `main()`.



---

**How it behaves across different builds**

| Build Target | Command | Preprocessor Action | Linker Result |
| --- | --- | --- | --- |
| **Normal App** | `g++ main.cpp -o app` | `UNIT_TEST` is unset $\rightarrow$ `main()` in `main.cpp` is **kept**. | Standard program runs using `main.cpp`'s entry point. |
| **Test Suite** | `g++ -DUNIT_TEST main.cpp test.cpp -o run_tests` | `UNIT_TEST` is set $\rightarrow$ `main()` in `main.cpp` is **stripped**. | Test suite runs using `test.cpp`'s entry point, linking `extractIPv4` seamlessly. |
```
### Prompt 4: Google Gemini 3.8 Flash Extended, Date:9/16/2026
```
when having a make file clean it has errors if run without the file able to be removed like rm main
```
### Output:
```
Add the **`-f` (force)** flag to your `rm` command:

clean:
	rm -f main test *.o


By default, `rm` exits with an error code if a specified file does not exist. When `make` sees any command return a non-zero exit status, it assumes the build step failed and aborts.

The `-f` flag does two things:

* Ignores non-existent files without returning an error code.
* Suppresses the `rm: cannot remove 'main': No such file or directory` warning output.

---

**Alternative: Tell Make to Ignore Errors**

You can also prefix any recipe line in a Makefile with a hyphen (`-`):

clean:
	-rm main


The `-` prefix tells `make` to ignore the error and continue execution even if the command fails, though `rm -f` is generally preferred because it also silences the terminal warning.

---

**Best Practice: Mark `clean` as `.PHONY**`

Always include `.PHONY: clean` at the top or bottom of your Makefile so that `make clean` continues to work even if someone accidentally creates a file named `clean` in the directory:

.PHONY: clean
clean:
	rm -f main test *.o

```
***