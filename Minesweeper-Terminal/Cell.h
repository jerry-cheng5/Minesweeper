#ifndef _CELL_H_
#define _CELL_H_
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
    void display_cell() const;
    void set_bomb_number();
    void reveal_cell();
    void toggle_flagged();
    void set_bomb();
    bool get_bomb();
    bool get_revealed();
    int get_bomb_number();

};


#endif