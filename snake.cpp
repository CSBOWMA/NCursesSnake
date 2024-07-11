#include "snake.h"
#include <random>
#include <ncurses.h>

//snakePiece



snakePiece::snakePiece(position pos, snakePiece* next) {
        this->pos = pos;
        this->next = next;
        }
snakePiece::snakePiece(position pos) {
            this->pos = pos;
            next = nullptr;
        }

//snake


snake::snake(position initial) {
        head = new snakePiece(initial);
        length = 0;
    }

snake::~snake() {
    iterator = head;
    while (iterator->next) {
    head = iterator->next;
    delete iterator;
    iterator = head; 
    }
    delete iterator;
}

    void snake::move (char direction) {
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

bool snake::colisionCheck(WINDOW *win) {
  
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

  void snake::printSnake(WINDOW *win) {

    iterator = head;
    mvwprintw (win, iterator->pos.y, iterator->pos.x, "0");

    for (int i = 0; i < length; i++) {
        
        iterator = iterator->next;
        mvwprintw(win, iterator->pos.y, iterator->pos.x, "O");

    }

    if(iterator->next != nullptr) {
       
        delete iterator->next;
        iterator->next = nullptr;
    }   

  }
void snake::fruitGenerate (WINDOW *win) {
      
    
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


void  snake::firstFruit(WINDOW *win) {
    fruitPosition.x = head->pos.x-5;
    fruitPosition.y = head->pos.y;
    mvwprintw(win, fruitPosition.y, fruitPosition.x, "@");
  }


