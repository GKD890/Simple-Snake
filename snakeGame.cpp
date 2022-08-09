#include<deque>
#include "snakeGame.h"
using namespace std;

// constructors
snakeGame::snakeGame() {
    HideCursor();
    srand(static_cast<unsigned int>(time(NULL)));
    beg = true;
    Snake temp1, temp2;
    while (1) {
        if (beg) { // if the first time run the game
            printMap();
            dir = _getch();
            initSnake();
            createFood();
            beg = eatFood = false;
        }
        temp2 = snake.back();
        temp1 = snake.front();
        snake.pop_back();
        if (eatFood) {
            temp2.image = '+';
            snake.push_back(temp2);
            eatFood = false;
        }
        else { clearSnake(temp2); };

        // Control direction
        if (dir == 's') ++temp1.y;
        else if (dir == 'a') --temp1.x;
        else if (dir == 'd') ++temp1.x;
        else               --temp1.x;

        try { ifCrash(); }
        catch (runtime_error& quitSignal) {
            throw quitSignal;
        }
        snake.front().image = '+';
        snake.push_front(temp1);
        printSnake();
        Sleep(speed + 30);
        if (temp1.x == food_x && temp1.y == food_y) EatFood();
        if (_kbhit())userInput();
    }
}

    // Control cursor
void snakeGame::gotoxy(short x, short y) {
        hOut = GetStdHandle(STD_OUTPUT_HANDLE); //TODO
        pos = { x,y };
        SetConsoleCursorPosition(hOut, pos);
    }
void snakeGame::HideCursor() {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO(CURSORINFO);
        GetConsoleCursorInfo(handle, &CURSORINFO);
        CURSORINFO.bVisible = false;
        SetConsoleCursorInfo(handle, &CURSORINFO);
    }
    // initialize Snake
    void snakeGame::initSnake( ) {
        snake.push_front({ '@',width / 2, height / 2 });
        for (int i = 0; i < 2; ++i) { snake.push_back({ '+',width / 2,height / 2 }); }
    }
    // if food is at the same position of snake
    int snakeGame::WrongLocation() {
        for (Snake body : snake) {
            if (body.x == food_x && body.y == food_y)return 0;
            else return 1;
        }
    }

    // produce food
    
    void snakeGame::createFood() {
        while (!WrongLocation()) {
            food_x = rand() % (width - 4) + 2;
            food_y = rand() % (width - 2) + 1;
        }
        gotoxy(food_x, food_y);
        cout << "*" << endl;
    }

    void snakeGame::printSnake() {
        deque<Snake>::const_iterator iter = snake.begin();
        for (; iter <= snake.begin() + 1 && iter < snake.end(); ++iter) {
            gotoxy(iter->x, iter->y);
            cout << iter->image;
        }
    }

    void snakeGame::clearSnake(Snake& tail) {
        gotoxy(tail.x, tail.y);
        cout << ' ';
    }

    void snakeGame::userInput() {
        char ch;
        switch (ch = _getch()) {
        case 'w':if (dir != 's')dir = ch; break;
        case 's':if (dir != 'w')dir = ch; break;
        case 'a':if (dir != 'd')dir = ch; break;
        case 'd':if (dir != 'a')dir = ch; break;
        case 'v':speed *= 0.8; break;
        case 'b':speed *= 1.4; break;
        case ' ':gotoxy(width / 2, height); cout << "game is paused, any key preseed continue"; _getch();
            gotoxy(width / 2, height); cout << "                    "; break;
        default:break;
        }
    }

    void snakeGame::EatFood() {
        createFood();
        eatFood = true;
        speed *= .8;
        ++score;
    }

    void snakeGame::ifCrash() {
        int flag = 0;
        if (snake.size() >= 5) {
            deque<Snake>::iterator iter = snake.begin() + 1;
            int x = (iter - 1)->x, y = (iter - 1)->y;
            for (; iter != snake.end(); ++iter) {
                if (iter->x == x && iter->y == y)flag = 1;
            }
        }
        if (flag || snake.front().x == 1 || snake.front().x == width - 2 || snake.front().y == 0 || snake.front().y == height - 1)
        {
            gotoxy(width / 2 - 10, height / 2);
            cout << "GAME OVER! '\n', Your score is: " << score << " \n Press ENTER to continue" << endl;
            while (1) {
                dir = _getch();
                if (dir == '\r')break;
            }
            runtime_error quit(" GAME OVER, QUIT"); throw quit;
        }
    }

    void snakeGame::printMap() {
        int i;
        for (i = 0; i != width; i += 2) cout << "&";
        gotoxy(0, 1);
        for (i = 1; i != height; ++i)cout << "&" << endl;
        for (i = 1; i != height; ++i) {
            gotoxy(width - 2, i);
            cout << "&" << endl;
        }
        gotoxy(0, height - 1);
        for (i = 0; i != width; i += 2)cout << "&";
        cout << "1. Press arrow to start 2. * is food  3. Space to pause \n 4. speed v+ b-";
    }
   
    

