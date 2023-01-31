#include "GameObjects.cpp"
#include "InputHandler.cpp"

using namespace std;

int main() {
    // Time Points For Delta Time
    auto timeA = chrono::system_clock::now();
    auto timeB = chrono::system_clock::now();

    InputHandler inputHandler;
    future<char> getInput = async(inputHandler.GetInput);
    chrono::seconds timeout(0);

    GameMaster game;
    Player* player = new Player(10, 10);
    Terrain* ground = new Terrain((int) screenHeight * 0.75, 0, (int) screenHeight * 0.25, screenWidth);

    game.AddObject(player);
    game.AddObject(ground);

    game.Display();
    // Game Loop
    bool stop = false;
    while (!stop) {
        game.Display();
        // Update Game Clock
        timeB = chrono::system_clock::now();
        chrono::duration <float> deltaTime = timeB - timeA;
        timeA = timeB;
        float elapsedTime = deltaTime.count();
        // Input / Test
        if (!game.AreColliding(player, ground)) {player->y++;}
        if (getInput.wait_for(timeout) == future_status::ready) {inputHandler.input = getInput.get(); getInput = async(inputHandler.GetInput);}
        if (inputHandler.input == 'q') {stop = true;}
    }

    return 0;
}