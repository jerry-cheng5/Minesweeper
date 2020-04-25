#ifndef _CELL_H_
#define _CELL_H_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

class Cell{

protected:

    bool flagged;
    bool revealed;
    int bomb_number;
    bool is_bomb;

public:

    //Constructors
    Cell();

    //Destructor
    ~Cell();

    //Methods
    sf::Sprite display_cell();
    void set_bomb_number();
    void reveal_cell();
    void flag();
    void deflag();
    void set_bomb();
    bool get_bomb();
    bool get_revealed();
    int get_bomb_number();
    bool get_flagged();

};


#endif