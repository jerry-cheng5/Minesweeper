#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_
#include <iostream>
#include <string>
#include <vector>
#include "Cell.h"
using namespace std;

class Gameboard{

private:

    vector <vector <Cell> > my_board;

public:

    //Constructors
    Gameboard();

    //Destructor
    ~Gameboard();

    //Methods
    void display_board(int n_flags) const;
    void init_bombs(size_t n_bombs);
    void increase_bomb_number(int j, int i);
    Cell get_cell(size_t j, size_t i);
    void reveal_cell(int j, int i);
    bool toggle_flagged(size_t j, size_t i, int n_flags);
    void reveal_bombs();
    bool check_win();

    //Debugging methods
    void reveal_all();
};


#endif