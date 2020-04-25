#include "Cell.h"
#include <iostream>
#include <string>
using namespace std;

//Constructors
Cell::Cell()
: flagged{false}, revealed{false}, bomb_number{0}, is_bomb{false}{}

//Destructor
Cell::~Cell(){}

//Methods
void Cell::display_cell() const{
    if(is_bomb == true){
        if(flagged == true)
            cout << "F ";
        else if(revealed == true)
            cout << "X ";
        else if(revealed == false && flagged == false)
            cout << "* ";
    }
    else{
        if(flagged == true)
            cout << "F ";
        else if(revealed == true)
            cout << bomb_number << " ";
        else if(revealed == false && flagged == false)
            cout << "* ";
    }
}

void Cell::set_bomb_number(){bomb_number++;}

void Cell::reveal_cell(){revealed = true;}

void Cell::toggle_flagged(){
    if (flagged == true)
        flagged = false;
    flagged = true;
}

void Cell::set_bomb(){is_bomb = true;}

bool Cell::get_bomb(){return is_bomb;}

bool Cell::get_revealed(){return revealed;}

int Cell::get_bomb_number(){return bomb_number;}