#include "src/Cell.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace sf;

//Constructors
Cell::Cell()
: flagged{false}, revealed{false}, bomb_number{0}, is_bomb{false}{}

//Destructor
Cell::~Cell(){}

//Methods
Sprite Cell::display_cell(){
    
    Texture t;
    if (!t.loadFromFile("images/tiles.jpg"))
        std::cout << "Error tiles.jpg not found." << std::endl;
    Sprite tile;
    tile.setTexture(t);
    int w = 32;
    
    if(is_bomb == true){
        if(flagged == true)
            tile.setTextureRect(IntRect(11*w, 0, w, w));
        else if(revealed == true)
            tile.setTextureRect(IntRect(9*w, 0, w, w));
        else if(revealed == false && flagged == false)
            tile.setTextureRect(IntRect(10*w, 0, w, w));
    }
    else{
        if(flagged == true)
            tile.setTextureRect(IntRect(11*w, 0, w, w));
        else if(revealed == true)
            tile.setTextureRect(IntRect(bomb_number*w, 0, w, w));
        else if(revealed == false && flagged == false)
            tile.setTextureRect(IntRect(10*w, 0, w, w));
    }
    return tile;
}

void Cell::set_bomb_number(){bomb_number++;}

void Cell::reveal_cell(){revealed = true;}

void Cell::flag(){flagged = true;}

void Cell::deflag(){flagged = false;}

void Cell::set_bomb(){
    is_bomb = true;
    bomb_number = 9;
}

bool Cell::get_bomb(){return is_bomb;}

bool Cell::get_revealed(){return revealed;}

int Cell::get_bomb_number(){return bomb_number;}

bool Cell::get_flagged(){return flagged;}