#include <curses.h>
#include <functional>
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
        char b = 'b';
        int birdPosX = 5;
        int birdPosY = 5;

};

void movement(int &y, Board& board){


    while (1)
    {
        std::this_thread::sleep_for(
                std::chrono::milliseconds(200)
                );
        board.set_field(5, y, ' ');
        if (y == 14 || y == 1) {
            board.set_field(5, y, 'b');
            continue;
        }
        else if (getch() == ' ') {
            flushinp(); 
            y--;
            board.set_field(5, y, 'b');
            continue;
        }
        y++;
        board.set_field(5, y, 'b');

    }
}
// this will propably be moved to board class
void keyPress(){
    while(1){
        int ch = getch();
        
        if(ch == 'q'){
            refresh();
            endwin();
            exit(0);
        }

        std::this_thread::sleep_for(
                std::chrono::milliseconds(50)
                );
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
    
    //thread for listening to key events
    std::thread mthread(movement, std::ref(bird.birdPosY), std::ref(board));
    std::thread fthread(keyPress) ;

    obstacle.make_obstacle(&board);

    while (1){
        werase(stdscr);

        board.display();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(50)
            );
    }
}
