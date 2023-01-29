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
    Terrain* ground = new Terrain(screenHeight * 0.75, 0, screenHeight * 0.25, screenWidth);

    game.AddObject(player);
    game.AddObject(ground);

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
    //     // Place Game Objects
    //     player->PutSprite();
    //     ground->PutSprite();
    //     // Check Input
    //     inputHandler.HandleInput();
    //     if (inputHandler.input == 'q') {stop = true;}
    // }

    return 0;
}