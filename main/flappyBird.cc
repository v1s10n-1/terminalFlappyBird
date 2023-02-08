#include "placeholder.h"
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

        void display(){
            for (int height = 0; height < 15; height++)
            {
                for (int width = 0; width < 63; width++)
                {
                    std::cout << board_table[width][height];

                }
                std::cout << std::endl;
            }
        }
};

int fall(unsigned char y)
{
    if (y >= 15)
    {
        return 0;
    }
    else
    {
        y++;
        return y;
    }
}

int main(int argc, char **argv)
{
    Board board;
    char bird = 'b';
    unsigned char birdPosX = 5;
    unsigned char birdPosY = 5;
    board.board_table[birdPosX][birdPosY] = bird;

    while (1)
    {
        system(sysClear.c_str());
        board.board_table[birdPosX][birdPosY] = ' ';
        birdPosY = fall(birdPosY);
        board.board_table[birdPosX][birdPosY] = bird;
        board.display();

        std::this_thread::sleep_for(
                std::chrono::milliseconds(500)
                );
    }
}
