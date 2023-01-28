#include <iostream>
#include <stdio.h>

using namespace std;

class GameObject {
    public:
        virtual ~GameObject() {ResetColor();}
        GameObject(char* sprite_, int posY_, int posX_) : 
            sprite(sprite_),
            posY(posY_),
            posX(posX_)
        {SetColor();}
        virtual void SetColor() {printf("\033[039m");}
        virtual void ResetColor() {printf("\033[039m");}
        virtual void PutSprite() {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    printf("\033[%d;%dH", posY + i, posX + j);
                    if (*(sprite + (i * width) + j) == '#') {cout << "\u2588";}
                    else {cout << *(sprite + (i * width) + j);}
                }
            }
        }
        static const int height = 3;
        static const int width = 3;
        int posY;
        int posX;
        char *sprite;
};

class Player : public GameObject {
    public:
        Player(char *playerSprite, int posY_, int posX_): 
            GameObject(playerSprite, posY_, posX_) 
        {SetColor();}
        virtual void SetColor() {printf("\033[32m");}
        static const int height = 2;
        static const int width = 2;
        char *sprite;
};

int main() {
    system("clear");
    char playerSprite[] = " #  # ";
    Player player(playerSprite, 10, 10);
    player.PutSprite();
    return 0;
}