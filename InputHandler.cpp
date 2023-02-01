#include "GameObjects.cpp"
#include <chrono>
#include <iostream>
#include <future>
#include <thread>

using namespace std;

class Command {
    public:
        virtual ~Command() {}
        virtual void Execute(Actor* actor) = 0;
};

class MoveRightCommand : public Command {
    public:
        virtual void Execute(Actor* actor) {actor->Move(true);}
};

class MoveLeftCommand : public Command {
    public:
        virtual void Execute(Actor* actor) {actor->Move(false);}
};

class JumpCommand : public Command {
    public:
        virtual void Execute(Actor* actor) {actor->Jump();}
};

class InputHandler {
    public:
        InputHandler() : 
            input('-') 
        {
            moveRight = new MoveRightCommand;
            moveLeft = new MoveLeftCommand;
        }
        ~InputHandler() {}
        Command* HandleInput() {
            switch (input) {
                case 'a':
                    return moveLeft;
                case 'd':
                    return moveRight;
                    break;
            }
            return NULL;
        }
        static char GetInput() {
            system("stty raw");
            char inChar = getchar();
            fflush(stdin);
            system("stty cooked"); 
            return inChar;   
        }
        char input;
    private:
        MoveRightCommand* moveRight;
        MoveLeftCommand* moveLeft;
};