//#include "placeholder.h"
//#include "placeholder.cc"
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>

// checking for operating system for console clearing not sure if it works i
// didn't test on windows and can't be bothered
#ifdef __unix__
std::string sysClear = "clear";

#elif defined(_WIN64)
std::string sysClear = "cls";
#endif


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
};


int fall(unsigned char y){
    if (y == 14){
        return 0;
    }
    else{
        y++;
        return y;
    }
}

int main(int argc, char **argv){
    Board board;
    Obstacle obstacle;
    Bird bird;

    obstacle.make_obstacle(&board);
    board.board_table[5][5] = bird.b;

    while (1){
        system(sysClear.c_str());
        board.board_table[bird.birdPosX][bird.birdPosY] = ' ';
        bird.birdPosY = fall(bird.birdPosY);
        board.board_table[bird.birdPosX][bird.birdPosY] = bird.b;
        board.display();

        std::this_thread::sleep_for(
                std::chrono::milliseconds(150)
                );
    }
}
