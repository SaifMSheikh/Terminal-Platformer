#include <iostream>
#include <stdio.h>

using namespace std;

const int screenHeight = 40;
const int screenWidth = 120;

class GameObject {
    public:
        virtual ~GameObject() {ResetColor();}
        GameObject(char* sprite_, int posY_, int posX_, int height_, int width_) : 
            sprite(sprite_),
            posY(posY_),
            posX(posX_),
            height(height_),
            width(width_)
        {}
        virtual void SetColor() {printf("\033[039m");}
        virtual void ResetColor() {printf("\033[039m");}
        virtual void PutSprite() {
            SetColor();
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    printf("\033[%d;%dH", posY + i, posX + j);
                    if (*(sprite + (i * width) + j) == '#') {cout << "\u2588";}
                    else {cout << *(sprite + (i * width) + j);}
                }
            }
        }
        int height;
        int width;
        int posY;
        int posX;
        int id;
        char *sprite;
};

class Player : public GameObject {
    public:
        Player(int posY_, int posX_): 
            GameObject((char*) "##", posY_, posX_, 2, 1) 
        {}
        virtual void SetColor() {printf("\033[32m");}
};

class Terrain : public GameObject {
    public:
        Terrain(int posY_, int posX_, int height_, int width_):
            GameObject(NULL, posY_, posX_, height_, width_)
        {}
        virtual void SetColor() {printf("\033[30m");}
        virtual void PutSprite() {
            SetColor();
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    printf("\033[%d;%dH", posY + i, posX + j);
                    cout << "\u2588";
                }
            }
        }
};

class GameMaster {
    public:
        GameMaster() :
            numberOfObjects(0)
        {}
        void AddObject(GameObject* newObject) {object[numberOfObjects++] = newObject;}
        void Display() {
            system("clear");
            for (int i = 0; i < numberOfObjects; i++) 
            {object[i]->PutSprite();}
        }
        unsigned int numberOfObjects;
        GameObject* object[25];
};

// int main() {
//     system("clear");
//     char playerSprite[] = "##";
//     Player player(playerSprite, 10, 10, 2, 1);
//     Terrain ground(screenHeight * 0.75, 0, screenHeight * 0.25, screenWidth);
    
//     return 0;
// }