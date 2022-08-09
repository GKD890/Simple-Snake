#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<deque>
#include<ctime>
#include<stdexcept>
#include "SnakeGame.h"
using namespace std;



int main() {
    system("mode con cols=120 lines=42");
    try { snakeGame game; }
    catch (runtime_error& gameEnd) {
        system("cls");
        cout << gameEnd.what();
        _getch();
    }
}
