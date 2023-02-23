#include <curses.h>
#include <unistd.h>
#include <thread>



int main(){

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE); 

    while (1){

    }
    refresh();
    endwin();
}
