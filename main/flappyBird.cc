#include "placeholder.h"
#include <iostream>
#include <unistd.h>

// checking for operating system for console clearing not sure if it works i
// didn't test on windows
#ifdef __unix__
std::string sysClear = "clear";

#elif defined(_WIN32)
std::string sysClear = "cls";
#endif

int fall(unsigned char y)
{
	if (y >= 15)
	{
		return 15;
	}
	else
	{
		y++;
		return y;
	}
}

int main(int argc, char **argv)
{
	char bird = 'b';
	char board[16][16] = {{0}};
	unsigned char birdPosX = 5;
	unsigned char birdPosY = 5;
	board[birdPosY][birdPosX] = bird;

	while (1)
	{
		system(sysClear.c_str());
		board[birdPosY][birdPosX] = ' ';
		birdPosY = fall(birdPosY);
		board[birdPosY][birdPosX] = 'b';

		
		for (int width = 0; width < 16; width++)
		{
			for (unsigned char height = 0; height < 16; height++)
			{
				std::cout << board[width][height];
			}
			std::cout << std::endl;
		}
	}
}
