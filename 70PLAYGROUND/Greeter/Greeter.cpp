#include "Greeter.hpp"
#include <iostream>
using namespace std;

Greeter::Greeter(const string& name) : userName(name) {
}

void Greeter::PrintGreeting() {
    cout << "Hello World, " << userName << "!" << endl;
}
