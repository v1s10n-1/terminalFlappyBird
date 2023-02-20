#include <curses.h>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <ncurses.h>

// TODO GOOD COMMENTS

//just board
class Board{
    public:
        char board_table[64][16] = {{}};

        Board(){
            for (int height = 0; height < 16; height++){
                for (int width = 0; width < 64; width++){
                    if(height == 15){
                        board_table[width][height] = *"x"; 
                    }else{
                        board_table[width][height] = *" "; 
                    }
                }
            }
        }

        void display(){
            for (int height = 0; height < 16; height++){
                for (int width = 0; width < 64; width++){
                    addch(board_table[width][height]);
                }
                addch(*"\n");
            }
        }

        void set_field(int x, int y, char value){
            board_table[x][y] = value;
        }
};

// obstacles that show
class Obstacle{
    public: 
    void make_obstacle(Board* board_table){
        for(int i = 15 - 1; i > 7; i--){
            board_table -> set_field(46, i, *"O");
        }
    }
};

// main character
class Bird{
    public:

        //for the future
    
        char b = 'b';
        int birdPosX = 5;
        int birdPosY = 5;

        int fall(unsigned char y){
            if (y == 14){
                return 0;
            }
            else{
                y++;
                return y;
            }
        }
};

// this will propably be moved to board class
void keyPress(){
    int ch = getch();

    if(ch == 'q'){
        refresh();
        endwin();
        exit(0);
    }

    // todo jumping
    else if(ch == ' '){
        //działa teraz dodać logike
    }
    else if (ch != ERR) {
        refresh();
        endwin();
        exit(1);
    }
}

int main(){
    
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE); //nie jestem pewien czy potrzebne w ogole, wyzej to samo
    
    Board board;
    Obstacle obstacle;
    Bird bird;
    
    std::thread fthread(keyPress);

    obstacle.make_obstacle(&board);
    board.board_table[5][5] = bird.b;

    while (1){
        werase(stdscr);

        board.board_table[bird.birdPosX][bird.birdPosY] = ' ';
        bird.birdPosY = bird.fall(bird.birdPosY);
        board.board_table[bird.birdPosX][bird.birdPosY] = bird.b;
        board.display();
        keyPress();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(1000)
            );
    }
}
