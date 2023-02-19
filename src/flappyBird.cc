#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <ncurses.h>

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

void keyPress(){
    int ch = getch();

    if(ch == 'q'){
        refresh();
        endwin();
        exit(0);
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
    
//    std::thread fthread(quit);
//    std::thread jthread(jump);    

    obstacle.make_obstacle(&board);
    board.board_table[5][5] = bird.b;

    while (1){
        werase(stdscr);

        board.board_table[bird.birdPosX][bird.birdPosY] = ' ';
        bird.birdPosY = bird.fall(bird.birdPosY);
        board.board_table[bird.birdPosX][bird.birdPosY] = bird.b;
        board.display();
        //refresh();
        keyPress();
        std::this_thread::sleep_for(
            std::chrono::milliseconds(5000)
            );
    }
}
