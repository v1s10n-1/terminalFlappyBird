#include <curses.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

//defines character it's position and current momentum
typedef struct Player{
    const char symbol[1];
    int pos_x;
    int pos_y;
    int momentum;
}Player;

typedef struct Obstacle{
    int obstacle_pos_x_curr;//x position of an obstacle
    int obstacle_pos_x_prev;//x position of an obstacle
    int free_space_y; //where on the y axis is the space where bird can pass through
}Obstacle;

//global variable for choosing index from a momentum_tab determining direction and momentum of falling/jumping
int mom_i = 0; 

//how much time passes between each tick
struct timespec ts = {0, 60000000};

//function for making bird fall in future it's gonna also handle going up, future me here, no it won't
void fall(Player* player, int diff);

void *input_capture();

void *space_input_capture();

void handle_obstacle(Obstacle obstacle[], WINDOW* win, int win_height);

void collision(Player* bird, Obstacle* obstacle, int win_height);

int main(){

    initscr();
    cbreak();
    noecho();
    
    curs_set(0);
    start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
    int height = 36;
    int width = 136; //window height and width
    int start_y = (LINES - height) / 2; 
    int start_x = (COLS - width) / 2; //variables for calculating where the middle of the screen is to display window there
    int momentum_tab[] = {-3, -3, -2, -1, 0, 2, 3}; //some things are just best hardcoded

    WINDOW* win = newwin(height, width, start_y, start_x); 
    refresh();
    wrefresh(win);

    box(win, 0, 0);

    struct Player bird = {"@", 16, 10, -1};

    struct Obstacle obstacle[5];
    obstacle[0] = (Obstacle){132, 132, rand() % 20 + 8};
    obstacle[1] = (Obstacle){158, 158, rand() % 20 + 8};
    obstacle[2] = (Obstacle){188, 188, rand() % 20 + 8};
    obstacle[3] = (Obstacle){214, 214, rand() % 20 + 8};
    obstacle[4] = (Obstacle){240, 240, rand() % 20 + 8};

    mvwhline(win, 35, 0, '#', 136);

    pthread_t thread[2];

    if(pthread_create(&thread[0], NULL, input_capture, NULL) != 0){
        printf("%s\n", "failed to create thread");
    }

    if(pthread_create(&thread[1], NULL, space_input_capture, NULL) != 0){
        printf("%s\n", "failed to create thread");
    }

    while (1){
        mvwprintw(win, bird.pos_y, bird.pos_x, "%s", " ");

        handle_obstacle(obstacle, win, height);

        fall(&bird, momentum_tab[mom_i]); //bird pointer

        mvwprintw(win, bird.pos_y, bird.pos_x, "%s", bird.symbol);

        collision(&bird, obstacle, height);

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

void *input_capture(){
    while(1){
        nanosleep(&ts, NULL);
        if (mom_i == 6) {
            continue;
        }
        mom_i++;
    }
}

void *space_input_capture(){
    while (1) {
        nanosleep(&ts, NULL);
        if (getch() == ' ') {
            mom_i = 0;
        }
    }
}

void handle_obstacle(Obstacle obstacle[], WINDOW* win, int win_height){
    for(int i = 0; i < 5; i++){
        if (obstacle[i].obastacle_pos_x_curr < 3) {
            obstacle[i].obastacle_pos_x_curr = 132;
            obstacle[i].free_space_y = rand() % 20 + 9;
        }
        mvwvline(win, 1, obstacle[i].obastacle_pos_x_prev, ' ', 34);

        mvwvline(win, 1, obstacle[i].obastacle_pos_x_curr, 'x', obstacle[i].free_space_y - 4);                          //needs to be 6 because of hard maths
        mvwvline(win, obstacle[i].free_space_y + 5, obstacle[i].obastacle_pos_x_curr, 'x', win_height - obstacle[i].free_space_y - 6); 
        obstacle[i].obastacle_pos_x_prev = obstacle[i].obastacle_pos_x_curr;
        obstacle[i].obastacle_pos_x_curr = obstacle[i].obastacle_pos_x_curr - 2;
    }
}

void collision(Player* bird, Obstacle obstacle[], int win_height){
    for (int i = 0; i < 5; i++ ) {
        if ((bird -> pos_x == obstacle[i].obastacle_pos_x_curr + 2) && 
                ((bird -> pos_y < (obstacle[i].free_space_y - 4)) || (bird -> pos_y > (obstacle[i].free_space_y + 5)))) {

            char str[] = "You lost LOL";

            attron(COLOR_PAIR(1));
            mvaddstr(LINES / 2, COLS / 2 - strlen(str) / 2, str);
            attroff(COLOR_PAIR(1));
            wrefresh(curscr);
            getch();

            endwin();
            _exit(0);
        } 
    }
}
