#include <ncurses.h>
#include <strstream>
#include <string>
#include <unistd.h>
#include <random>
#include "snake.h"

WINDOW* menuScreen(WINDOW* win, int score) {

    wclear(win);
    mvwprintw(win, getmaxy(win)/2, getmaxx(win)/2-10, "Press enter to start");

    mvwprintw(win, getmaxy(win)/2-5, getmaxx(win)/2-8, "Press q to exit");
    wborder(win, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219);
    curs_set(0);
    wrefresh(win);
    int input = getch();
    while(input != 10) { 
        if (input == 'q') {
            endwin();
            exit(0);
        }
        input = getch();
    }
    wclear(win);
    return win;
}

char userInput(char direction, WINDOW *win) {
  nodelay(win, true);
timeout(0);  
  
    switch (getch()) {
        case 'w':
            return 'w';
        case 'a':
            return 'a';
        case 's':
            return 's';
        case 'd':
            return 'd';
        default:

        return direction;

    }
}

WINDOW* windowInit() {
    initscr();
    WINDOW *win = newwin(0, 0, 0, 0);  
    wborder(win, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219);
    curs_set(0);

    mvwprintw(win, getmaxy(win)/2, getmaxx(win)/2-15, "Please press a button to start");

    refresh();
    wrefresh(win);
    getchar();
    wclear(win);
    return win;
}


int snakeGame(WINDOW* win) {

    wrefresh(win);
    position initial;
    initial.x = getmaxx(win)/2;
    initial.y = getmaxy(win)/2;
    snake gameSnake(initial);
    position fruit;
    char direction = 'a';

    wborder(win, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219);
    gameSnake.printSnake(win); 
    gameSnake.firstFruit(win);
    wrefresh(win);
    wclear(win);
    while(true) {

        direction = userInput(direction, win);
        gameSnake.move(direction);
        if(gameSnake.colisionCheck(win)) {

            
            return gameSnake.length;
        }
        wclear(win);
        gameSnake.fruitGenerate(win);
        gameSnake.printSnake(win);
        wborder(win, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219);
        curs_set(0);
        wrefresh(win); 
        usleep(100000); 

    }

}

void gameOver (WINDOW* win, int score) {
   wclear(win); 
   wborder(win, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219);
   mvwprintw(win, getmaxy(win)/2-5, getmaxx(win)/2-5, "Game Over");
   mvwprintw(win, getmaxy(win)/2, getmaxx(win)/2-4/*+static_cast<int>(log10(score)) + 1*/, "Score: %d", score);
   mvwprintw(win, getmaxy(win)/2+5, getmaxx(win)/2-12, "Press enter to continue");
   timeout(1000000000);
   nodelay(win, false);
   wrefresh(win);
   while (getch() != 10);
 }


int main(int argc, char **argv) {

    WINDOW *win = windowInit();
    int score = 0;
    int highScore = 0;
    int windowHeight = getmaxy(win);
    int windowWidth = getmaxx(win);
    int screen[windowWidth][windowHeight];
    position snakeHead;
    while (true) {
        win = menuScreen(win, score);
        score = snakeGame(win);
        gameOver(win, score);

    }

    endwin();
    return 0;
}
