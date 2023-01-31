#include <chrono>
#include <iostream>
#include <future>
#include <thread>

using namespace std;

class Command {
    public:
        virtual ~Command() {}
        virtual void Execute() = 0;
};

class InputHandler {
    public:
        InputHandler() : input('-') {}
        ~InputHandler() {}
        static char GetInput() {
            system("stty raw");
            char inChar = getchar();
            system("stty cooked"); 
            return inChar;   
        }
        char input;
};

// int main() {
//     InputHandler inputHandler;
//     while (inputHandler.GetInput() != 'q') {inputHandler.HandleInput();}
//     return 0;
// }