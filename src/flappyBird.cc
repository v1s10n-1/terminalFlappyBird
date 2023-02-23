#include <curses.h>


int main(){

    initscr();
    cbreak();
    noecho();

    int height = 16;
    int width = 64;
    int start_y = (LINES - height) / 2;
    int start_x = (COLS - width) / 2;

    WINDOW * win = newwin(height, width, start_y, start_x); 
    refresh();

    intrflush(win, FALSE);
    keypad(win, TRUE);
    nodelay(win,TRUE);
    scrollok(win, TRUE); 

    box(win, 0, 0);
    wrefresh(win);






/*
    while (1){

    }
*/

    getch();

    endwin();
}
