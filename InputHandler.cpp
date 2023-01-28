#include <iostream>
#include <thread>

using namespace std;

class Command {
    public:
        virtual ~Command() {}
        virtual void Execute() = 0;
};

class InputHandler {
    public:
        InputHandler() {system("stty raw");}
        ~InputHandler() {system("stty cooked");}
        void HandleInput() {input = getchar();}
        char GetInput() {return input;}
    private:
        char input;
};

int main() {
    InputHandler inputHandler;
    while (inputHandler.GetInput() != 'q') {inputHandler.HandleInput();}
    return 0;
}