#include <ncurses.h>
#include <strstream>
#include <string>
#include <unistd.h>
#include <random>
struct position {
    int x;
    int y;

};

class snakePiece {
    public:
        position pos;
        snakePiece *next;
        snakePiece(position pos, snakePiece* next) {
        this->pos = pos;
        this->next = next;
        }
        snakePiece(position pos) {
            this->pos = pos;
            next = nullptr;
        }
            
};

class snake {



    public:
    snake(position initial) {
        head = new snakePiece(initial);
        length = 0;
    }
    snakePiece* head;
    snakePiece* iterator;
    int length;
    position fruitPosition;

    ~snake() {

        iterator = head;
        while (iterator->next) {
        head = iterator->next;
        delete iterator;
        iterator = head; 
        }
        delete iterator;

    }
    


    void move (char direction) {
        snakePiece *nextPiece = new snakePiece(head->pos, head);
         
        switch (direction) {
            case 'w':
                nextPiece->pos.y -=1;       
                break;
            case 'a':
                nextPiece->pos.x -=1;       
                break;
            case 's':
                nextPiece->pos.y +=1;
                break;
            case 'd':
                nextPiece->pos.x +=1;
                break;
            default:
                nextPiece->pos.x -=1;
        }

         
        if (length != 0 && nextPiece->pos.x == head->next->pos.x && nextPiece->pos.y == head->next->pos.y) {
            
        switch (direction) {
            case 'w':
                nextPiece->pos.y +=2;       
                break;
            case 'a':
                nextPiece->pos.x +=2;       
                break;
            case 's':
                nextPiece->pos.y -=2;
                break;
            case 'd':
                nextPiece->pos.x -=2;
                break;
        }
        }
        
        head = nextPiece;
    }
  bool colisionCheck(WINDOW *win) {
    
      if (!head->next){
        return false;
      }
      iterator = head->next;
      while (iterator->next) {
        iterator = iterator->next;
        if (head->pos.x == iterator->pos.x && head->pos.y == iterator->pos.y) {
            return true;
        }
      }
    if (head->pos.x == 0 || head->pos.y == 0) {
        return true;
    }

    if (head->pos.x == getmaxx(win)-1 || head->pos.y == getmaxy(win)-1) {
        return true;
    }

    return false;

  }  

  void printSnake(WINDOW *win) {

    iterator = head;
    mvwprintw (win, iterator->pos.y, iterator->pos.x, "0");

    for (int i = 0; i < length; i++) {
        
        iterator = iterator->next;
        mvwprintw(win, iterator->pos.y, iterator->pos.x, "O");

    }

    //this may be a ticking time bomb of a solution, but it seems to work
    if(iterator->next != nullptr) {
       
        delete iterator->next;
        iterator->next = nullptr;
    }   

  }

  void fruitGenerate (WINDOW *win) {
        
      
      if(head->pos.x == fruitPosition.x && head->pos.y == fruitPosition.y) {
        length++;
        
        srand((unsigned) time(NULL));
        int random = rand();
        while (true) {
            fruitPosition.x = rand()%(getmaxx(win)-3)+1;
            fruitPosition.y = rand()%(getmaxy(win)-3)+1;
            iterator = head;
            
            while(iterator->next) {
                if (iterator->pos.x != fruitPosition.x && iterator->pos.y != fruitPosition.y) {
                    iterator = iterator->next;
                } else {
                break; 
                }
            }
            if (!iterator->next) {
                break;
            }
        }
        
      }

        mvwprintw(win, fruitPosition.y, fruitPosition.x, "@");
  }

void  firstFruit(WINDOW *win) {
    fruitPosition.x = head->pos.x-5;
    fruitPosition.y = head->pos.y;
    mvwprintw(win, fruitPosition.y, fruitPosition.x, "@");
  }
};
WINDOW* windowInit() {
    initscr();
    WINDOW *win = newwin(0, 0, 0, 0);  
    wborder(win, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219);
    curs_set(0);

    mvwprintw(win, getmaxy(win)/2, getmaxx(win)/2-15, "Please press a button to start");

    mvwprintw(win, getmaxy(win)-1, getmaxx(win)-1, "0");
    mvwprintw(win, 0, 0, "0");
    refresh();
    wrefresh(win);
    getchar();
    wclear(win);
    return win;
}

WINDOW* menuScreen(WINDOW* win, int score) {


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

int snakeGame(WINDOW* win) {

    wrefresh(win);
    position initial;
    initial.x = getmaxx(win)/2;
    initial.y = getmaxy(win)/2;
    snake gameSnake(initial);
    position fruit;
    char direction = 'a';
    int score = 0;

    wborder(win, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219);
    gameSnake.printSnake(win); 
    gameSnake.firstFruit(win);
    wrefresh(win);
    wclear(win);
    while(true) {

        direction = userInput(direction, win);
        gameSnake.move(direction);
        if(gameSnake.colisionCheck(win)) {

            
            break;
        }
        wclear(win);
        gameSnake.fruitGenerate(win);
        gameSnake.printSnake(win);
        wborder(win, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219);
        curs_set(0);
        wrefresh(win);
     
        usleep(100000); 

    }

    return score;
}

WINDOW* gameOver (WINDOW* win, int score) {

    return {};
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
       // gameOver(win);

    }

    refresh();
    mvwprintw(win, (windowHeight/2), (windowWidth/2), "O");



    // refreshing the window
    wrefresh(win);

    getch();
    endwin();
    return 0;
}
