#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H
#include <SFML/Graphics.hpp>
#include <iostream>

enum gameMode {EASY, MEDIUM, HARD};
enum gameState {MENU, RUN, END};

struct Snake{
    int x,y;
};

struct Fruit{
    int x,y;
};

class Game {
public:
    gameMode mode;
    gameState state = MENU;
    int squareSize = 34;
    int screenWidth = squareSize*squareSize;
    int screenHeight = squareSize*squareSize/2;
    int xLine = squareSize;
    int yLine = squareSize/2;
    Snake wonsz[99];
    Fruit apple;
    float czas = 0;
    float delay; // "predkosc" weza :)
    int snakeLength = 3;
    int direction = 2; // dir 0 - dol, dir 1 - lewo , dir 2 - prawo, dir 3 - gora
    void play();
    void snakeLogic();
    Game();
};


#endif //SNAKE_GAME_H
