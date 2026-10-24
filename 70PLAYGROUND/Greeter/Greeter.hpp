#pragma once
#include <string>
using namespace std;

class Greeter {
public:
    Greeter(const string& name);      // stores the name to greet
    void PrintGreeting();             // prints "Hello World, <name>!"

private:
    string userName;
};
