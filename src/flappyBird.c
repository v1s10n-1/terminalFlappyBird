#include <curses.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>

//defines character it's position and current momentum
typedef struct Player{
    const char symbol[1];
    int pos_x;
    int pos_y;
    int momentum;
}Player;

typedef struct Obstacle{
    int obastacle_pos_x; //x position of an obstacle
    int free_space_y; //where on the y axis is the space where bird can pass through
}Obstacle;

//global variable for choosing index from a momentum_tab determining direction and speed of falling/jumping
int mom_i = 0; 

//how much time passes between each tick
struct timespec ts = {0, 60000000};

//function for making bird fall in future it's gonna also handle going up, future me here, no it won't
void fall(Player* player, int diff);

void *input_capture(void* arg);

void *space_input_capture(void* arg);

void handle_obstacle(Obstacle* obstacle, WINDOW* win);

int main(){

    initscr();
    cbreak();
    noecho();

    int height = 36;
    int width = 135; //window height and width
    int start_y = (LINES - height) / 2; 
    int start_x = (COLS - width) / 2; //variables for calculating where is the middle of the screen to display window there
    int momentum_tab[] = {-3, -3, -2, -1, 0, 2, 3}; //some things are just best hardcoded

    WINDOW* win = newwin(height, width, start_y, start_x); 
    refresh();
    wrefresh(win);

    box(win, 0, 0);

    struct Player bird = {'@', 16, 10};

    struct Obstacle obstacle = {110, rand() % 15};

    mvwhline(win, 35, 0, '#', 135);

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

        handle_obstacle(&obstacle, win);

        fall(&bird, momentum_tab[mom_i]); //bird pointer

        mvwprintw(win, bird.pos_y, bird.pos_x, "%s", bird.symbol);

        wrefresh(win);

        nanosleep(&ts, NULL);
    }

    endwin();
    return 0;
}

void fall(Player* player, int diff){
    if(player -> pos_y < 4){
        player -> pos_y = 4;
    }else if(player -> pos_y > 31){
        player -> pos_y = 31;
    }
    
    player -> pos_y = player -> pos_y + diff;
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

void handle_obstacle(Obstacle* obstacle, WINDOW* win){
    mvwprintw(win, obstacle -> free_space_y, obstacle -> obastacle_pos_x, "%s", " ");
    
    obstacle -> obastacle_pos_x = obstacle -> obastacle_pos_x - 2;
    
    mvwprintw(win, obstacle -> free_space_y, obstacle -> obastacle_pos_x, "%s", "A");
}



