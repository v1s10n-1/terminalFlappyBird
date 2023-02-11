#include "placeholder.h"

Board::Board(){
    for (int height = 0; height < 15; height++)
    {
        for (int width = 0; width < 63; width++)
        {
            board_table[width][height] = *" "; 
        }
    }
}

void Board::display(){
    for (int height = 0; height < 15; height++)
    {
        for (int width = 0; width < 63; width++)
        {
            std::cout << board_table[width][height];

        }
        std::cout << std::endl;
    }
};
