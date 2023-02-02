#include "InputHandler.cpp"

using namespace std;

int main() {
    // Time Points For Delta Time
    auto timeA = chrono::system_clock::now();
    auto timeB = chrono::system_clock::now();

    // Initialize Input Thread
    InputHandler inputHandler;
    future<char> getInput = async(inputHandler.GetInput);
    chrono::seconds timeout(0);

    // Create Game Objects
    GameMaster game;
    Player* player = new Player(25, 25);
    Terrain* ground = new Terrain((int) screenHeight * 0.75, 0, (int) screenHeight * 0.25, screenWidth);
    Terrain* obstacle = new Terrain(20, 20, 5, 5);
    game.AddObject(player);
    game.AddObject(ground);
    game.AddObject(obstacle);

    game.Display();
    game.HandleCollision(player, obstacle);

    // Game Loop
    // bool stop = false;
    // while (!stop) {
    //     // Display Frame
    //     game.Display();

    //     // Update Game Clock
    //     timeB = chrono::system_clock::now();
    //     chrono::duration <float> deltaTime = timeB - timeA;
    //     timeA = timeB;
    //     float elapsedTime = deltaTime.count();

    //     // Test
    //     while (!game.AreColliding(player, ground)) {player->y++;}
    //     Command* command = inputHandler.HandleInput();
    //     if (command) {
    //         if (inputHandler.input == 'q') {stop = true;}
    //         else {command->Execute(player);}
    //         inputHandler.input = '-';
    //     }

    //     // Get Input
    //     if (getInput.wait_for(timeout) == future_status::ready) {
    //         inputHandler.input = getInput.get();

    //         Command* command = inputHandler.HandleInput();
    //         if (command) {command->Execute(player);}

    //         getInput = async(inputHandler.GetInput);
    //         if (inputHandler.input == 'q') {stop = true;}
    //     }
    // }

    return 0;
}