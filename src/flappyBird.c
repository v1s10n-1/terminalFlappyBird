#include <curses.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

//defines character it's position and current momentum
struct Player{
    const char symbol[1];
    int pos_x;
    int pos_y;
    int momentum;
};

int mom_i = 0;    

typedef struct Player Player;

//how much time passes between each tick of the bird falling 
struct timespec ts = {0, 60000000};

//function for making bird fall in future it's gonna also handle going up, future me here, no it won't
void fall(Player* player, int diff);

void *input_capture(void* arg);

void *space_input_capture(void* arg);

int main(){

    initscr();
    cbreak();
    noecho();

    int height = 24;
    int width = 72;
    int start_y = (LINES - height) / 2;
    int start_x = (COLS - width) / 2;
    int row, col;
    int momentum_tab[] = {-2, -2, -1, -1, 0, 1, 2};

    WINDOW* win = newwin(height, width, start_y, start_x); 
    refresh();
    wrefresh(win);

    box(win, 0, 0);

    getmaxyx(win, col, row);

    struct Player bird = {'@', 10, 10};
    Player* bptr = &bird;

    mvwhline(win, 23, 0, '#', 72);


    pthread_t thread[2];

    if(pthread_create(&thread[0], NULL, input_capture, NULL) != 0){
        printf("%s\n", "failed to create thread");
    }

    pthread_t s_thread;
    if(pthread_create(&thread[1], NULL, space_input_capture, NULL) != 0){
        printf("%s\n", "failed to create thread");
    }

    while (1){
        mvwprintw(win, bird.pos_y, bird.pos_x, "%s", " ");

        fall(bptr, momentum_tab[mom_i]); //bird pointer

        mvwprintw(win, bird.pos_y, bird.pos_x, "%s", bird.symbol);

        wrefresh(win);

        nanosleep(&ts, NULL);
    }

    endwin();
    return 0;
}

void fall(Player* player, int diff){
    
    // to nie działa kompletnie, trzeba naprawić żeby sobie mógł rozbijać głowę o sufit, a nie odlatywać
    
    player->pos_y = player -> pos_y + diff;
}

void *input_capture(void* arg){
    while(1){
        nanosleep(&ts, NULL);
        if (mom_i == 6) {
            continue;
        }
        mom_i++;
    }
}
void *space_input_capture(void* arg){
    while (1) {
        nanosleep(&ts, NULL);
        if (getch() == ' ') {
            printw("%s  ", "working");
            mom_i = 0;
        }
    }
}




