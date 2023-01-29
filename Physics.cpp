#include "GameObjects.cpp"
#include "InputHandler.cpp"
#include <chrono>
#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
    // Time Points For Delta Time
    auto timeA = chrono::system_clock::now();
    auto timeB = chrono::system_clock::now();

    InputHandler inputHandler;

    GameMaster game;
    Player* player = new Player(10, 10);
    Terrain* ground = new Terrain((int) screenHeight * 0.75, 0, (int) screenHeight * 0.25, screenWidth);
    Terrain* obstacle = new Terrain(ground->y - 2, 100, 2, 5);

    game.AddObject(player);
    game.AddObject(ground);
    game.AddObject(obstacle);

    game.Display();

    // bool stop = false;
    // while (!stop) {
    //     // Clear Screen
    //     system("clear");
    //     // Update Game Clock
    //     timeB = chrono::system_clock::now();
    //     chrono::duration <float> deltaTime = timeB - timeA;
    //     timeA = timeB;
    //     float elapsedTime = deltaTime.count();
    //     // Check Input
    //     inputHandler.HandleInput();
    //     if (inputHandler.input == 'q') {stop = true;}
    // }

    return 0;
}