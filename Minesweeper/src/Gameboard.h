#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "src/Cell.h"
using namespace sf;

class Gameboard{

private:

    std::vector <std::vector <Cell> > my_board;

public:

    //Constructors
    Gameboard();

    //Destructor
    ~Gameboard();

    //Methods
    void display_board(RenderWindow *window);
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