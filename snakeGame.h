#ifndef SNAKE_H
#define SNAKE_H

#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<deque>
#include<ctime>
#include<stdexcept>

struct Snake {
    char image;
    short x, y;
};

class snakeGame{
    private:
        
        enum MapSize { height = 40, width = 120 };
        HANDLE hOut; COORD pos;
        char dir;
        bool beg, eatFood = false;
        double speed = 200;
 //       deque<unique_ptr<Snake>> snake;
        std::deque<Snake> snake;
        int food_x, food_y;
        int score = 0;

    public:
        snakeGame();
        void gotoxy(short x, short y);
        void HideCursor();
        void userInput();
        

        void initSnake();
        void printSnake();
        void clearSnake(Snake& tail);
        int WrongLocation();

        void createFood();
        void EatFood();
        void ifCrash();
        void printMap();
};
#endif // !snake







