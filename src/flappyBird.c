#include <curses.h>
#include <unistd.h>
#include <time.h>


//defines character and it's starting position
struct Player{
    const char symbol[1];
    int pos_x;
    int pos_y;
};

typedef struct Player Player;

//how much time passes between each time the bird is falling
struct timespec ts = {0, 35000000};

//function for making bird fall in future it's gonna also handle going up
void fall(Player* player);


int main(){

    initscr();
    cbreak();
    noecho();

    int height = 24;
    int width = 72;
    int start_y = (LINES - height) / 2;
    int start_x = (COLS - width) / 2;
    int row, col;

    WINDOW * win = newwin(height, width, start_y, start_x); 
    refresh();
    wrefresh(win);

    box(win, 0, 0);

    getmaxyx(win, col, row);

    struct Player bird = {'@', 10, 10};
    Player *bptr = &bird;
    
    mvwhline(win, 23, 0, '#', 72);

    while (1){
        mvwprintw(win, bird.pos_y, bird.pos_x, "%s", " ");

        fall(bptr);

        mvwprintw(win, bird.pos_y, bird.pos_x, "%s", bird.symbol);

        wrefresh(win);
   
        nanosleep(&ts, NULL);
    }

    endwin();
}

void fall(Player* player){
    if (player->pos_y > 21) {
        return;
    }
    player->pos_y++;
}








