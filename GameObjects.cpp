#include <iostream>
#include <stdio.h>

using namespace std;

const int screenHeight = 40;
const int screenWidth = 120;

class GameObject {
    public:
        virtual ~GameObject() {ResetColor();}
        GameObject(char* sprite_, int y_, int x_, int height_, int width_) : 
            sprite(sprite_),
            y(y_),
            x(x_),
            height(height_),
            width(width_)
        {}
        virtual void SetColor() {printf("\033[039m");}
        virtual void ResetColor() {printf("\033[039m");}
        virtual void PutSprite() {
            SetColor();
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    printf("\033[%d;%dH", y + i, x + j);
                    if (*(sprite + (i * width) + j) == '#') {cout << "\u2588";}
                    else {cout << *(sprite + (i * width) + j);}
                }
            }
            ResetColor();
        }
        int height;
        int width;
        int y;
        int x;
        int id;
        char *sprite;
};

class Player : public GameObject {
    public:
        Player(int y_, int x_): 
            GameObject((char*) "##", y_, x_, 2, 1) 
        {}
        virtual void SetColor() {printf("\033[32m");}
};

class Terrain : public GameObject {
    public:
        Terrain(int y_, int x_, int height_, int width_):
            GameObject(NULL, y_, x_, height_, width_)
        {}
        virtual void SetColor() {printf("\033[30m");}
        virtual void PutSprite() {
            SetColor();
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    printf("\033[%d;%dH", y + i, x + j);
                    cout << "\u2588";
                }
            }
            ResetColor();
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
        bool AreColliding(GameObject* A, GameObject* B) {
            // Colliding If Same Position
            if (A->y == B->y && A->x == B->x) {return true;}
            bool yOverlap = false;
            // Test Height
            if (A->y > B->y) {
                if (B->height > (A->y - B->y)) {yOverlap = true;}
            }
            if (A->height > (B->y - A->y)) {yOverlap = true;}
            if (!yOverlap) {return false;}
            // Test Width
            if (A->x > B->x) {
                if (B->width > (A->x - B->x)) {return true;}
            }
            if (A->width > (B->x - A->x)) {return true;}
            // Not Colliding
            return false;
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