//#include "placeholder.h"
//#include "placeholder.cc"
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <termios.h>

std::string sysClear = "clear";

char getch() {
    char buf = 0;
    struct termios old = { 0 };
    fflush(stdout);
    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
    old.c_lflag    &= ~ICANON;   // local modes = Non Canonical mode
    old.c_lflag    &= ~ECHO;     // local modes = Disable echo. 
    old.c_cc[VMIN]  = 1;         // control chars (MIN value) = 1
    old.c_cc[VTIME] = 0;         // control chars (TIME value) = 0 (No time)
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0) perror("read()");
    old.c_lflag    |= ICANON;    // local modes = Canonical mode
    old.c_lflag    |= ECHO;      // local modes = Enable echo. 
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror ("tcsetattr ~ICANON");
    return buf;
}

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
                    std::cout << board_table[width][height];

                }
                std::cout << std::endl;
            }
        }

        void set_field(int x, int y, char value){
            board_table[x][y] = value;
        }
};

class Obstacle{
    public: 
    void make_obstacle(Board* board_table){
        for(int i = 15 - 1; i > 7; i--){
            board_table -> set_field(46, i, *"O");
        }
    }
};

class Bird{
    public:
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

// function for capturing keypress

void quit(){
    while(1){
        if(getch() == ' '){
            exit(0);
        }
    }
}


int main(int argc, char **argv){

    std::thread thread(quit);
    
    Board board;
    Obstacle obstacle;
    Bird bird;
    
    obstacle.make_obstacle(&board);
    board.board_table[5][5] = bird.b;

    while (1){
        system(sysClear.c_str());
        board.board_table[bird.birdPosX][bird.birdPosY] = ' ';
        bird.birdPosY = bird.fall(bird.birdPosY);
        board.board_table[bird.birdPosX][bird.birdPosY] = bird.b;
        board.display();

            std::this_thread::sleep_for(
                std::chrono::milliseconds(150)
                );
    }
}
