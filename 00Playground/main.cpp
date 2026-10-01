#include "Greeter/Greeter.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    string inputName = "Florian";      
    if (argc > 1) {
        inputName = argv[1];
    }

    Greeter greeter(inputName);
    greeter.PrintGreeting();

    return 0;
}
