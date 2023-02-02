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
                    printf("\033[%d;%dH", (int) y + i, (int) x + j);
                    if (*(sprite + (i * width) + j) == '#') {cout << "\u2588";}
                    else {cout << *(sprite + (i * width) + j);}
                }
            }
            ResetColor();
        }
        int height;
        int width;
        float y;
        float x;
        unsigned int id;
        char *sprite;
};

class Actor : public GameObject {
    public:
        Actor(char * sprite_, int y_, int x_, int height, int width):
            GameObject(sprite_, y_, x_, height, width)
        {}
        void Move(bool right) {if (right) {x++;} else {x--;}}
        void Jump() {}
};

class Player : public Actor {
    public:
        Player(int y_, int x_): 
            Actor((char*) "##", y_, x_, 2, 1) 
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
                    printf("\033[%d;%dH", (int) (y + i), (int) (x + j));
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
        void HandleCollision(GameObject* A, GameObject* B) {
            switch (CheckCollision(A, B)) {
                case 0:     // Not Colliding
                    cout << "NOT COLLIDING"; 
                    break;
                case 1:     // Sprites Overlap
                    cout << "OVERLAP";
                    break;
                case 2:     // A Below B
                    cout << "A ABOVE B";
                    break;
                case 3:     // A Above B
                    cout << "A BELOW B";
                    break;
                case 4:     // B A
                    cout << "A LEFT B";
                    break;
                case 5:     // A B
                    cout << "A RIGHT OF B";
                    break;
            }
        }
        int CheckCollision(GameObject* A, GameObject* B) {
            bool xOverlap = false;
            bool yOverlap = false;
            for (int x = A->x; x < (A->x + A->width); x++) {
                if (x >= B->x && x < (B->x + B->width)) {xOverlap = true; cout << 'X';}
            }
            for (int y = A->y; y < (A->y + A->height); y++) {
                if (y >= B->y && y < (B->y + B->height)) {yOverlap = true; cout << 'Y';}
            }
            if (xOverlap && yOverlap) {return 1;}                               // Overlap
            if (xOverlap) {
                if ((A->y + A->height) == B->y) {return 2;}                 // A Above B
                if (A->y == (B->y + B->height)) {return 3;}                 // A Below B
            }
            if (yOverlap) {
                if ((A->x + A->width) == B->x) {return 4;}                 // A Left B
                if (A->x == (B->x + B->width)) {return 5;}                 // A Right B
            }
            return 0;
        }
                                                                     
                
        unsigned int numberOfObjects;
        GameObject* object[25];
};