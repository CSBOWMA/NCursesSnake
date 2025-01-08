#ifndef SNAKE_H
#include <ncurses.h>
#include <random>
#define SNAKE_H


struct position {
    int x;
    int y;
};

class snakePiece {
    public:
        position pos;
        snakePiece *next;
        snakePiece(position pos, snakePiece* next);
        snakePiece(position pos); 

};

class snake {



    public:
        snake(position initial);
        snakePiece* head;
        snakePiece* iterator;
        int length;
        position fruitPosition;

        ~snake();

        bool colisionCheck(WINDOW *win);



        void move (char direction);
        void printSnake(WINDOW *win);
        void fruitGenerate (WINDOW *win);
        void  firstFruit(WINDOW *win);
};

#endif
