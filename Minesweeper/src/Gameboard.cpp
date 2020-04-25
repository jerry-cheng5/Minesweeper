#include "src/Gameboard.h"
#include "src/Cell.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h> 
#include <time.h>
using namespace sf;

//Constructors
Gameboard::Gameboard(){
    for(int j=0; j<10; j++){
        my_board.push_back(std::vector<Cell>());
        for(int i=0; i<10; i++){
            my_board[j].push_back(Cell());
        }
    }
}

//Destructors
Gameboard::~Gameboard(){}

//Methods
void Gameboard::display_board(RenderWindow *window){
    for(int i=0; i<my_board[0].size(); i++){
        for(int j=0; j<my_board.size(); j++){
            Sprite tile = my_board[i].at(j).display_cell();
            (*window).draw(tile);
        }
    }
}

void Gameboard::init_bombs(size_t n_bombs){
    srand (time(NULL));
    int counter = 0;
    while(counter < n_bombs){
        int j = rand() % 10;
        int i = rand() % 10;

        if(my_board[j].at(i).get_bomb() == false){
            my_board[j].at(i).set_bomb();

            increase_bomb_number(j+1, i-1);
            increase_bomb_number(j+1, i);
            increase_bomb_number(j+1, i+1);
            increase_bomb_number(j, i-1);
            increase_bomb_number(j, i+1);
            increase_bomb_number(j-1, i-1);
            increase_bomb_number(j-1, i);
            increase_bomb_number(j-1, i+1);

            counter++;
        }
    }
}

void Gameboard::increase_bomb_number(int j, int i){
    if(j < 10 && j >= 0 && i < 10 && i >= 0 && my_board[j].at(i).get_bomb() == false){
        my_board[j].at(i).set_bomb_number();
    }
}

Cell Gameboard::get_cell(size_t j, size_t i){
    Cell temp = my_board[j].at(i);
    return temp;
}

void Gameboard::reveal_bombs(){
    for(int j=0; j<10; j++){
        for(int i=0; i<10; i++){
            if(my_board[j].at(i).get_bomb() == true)
                my_board[j].at(i).reveal_cell();
        }
    }
}

bool Gameboard::check_win(){
    int counter = 0;
    for(int j=0; j<10; j++){
        for(int i=0; i<10; i++){
            if(my_board[j].at(i).get_bomb() == false && my_board[j].at(i).get_revealed() == true)
                counter++;
        }
    }
    if(counter == 90)
        return true;
    return false;
}

void Gameboard::reveal_cell(int j, int i){
    if(j < 10 && j >= 0 && i < 10 && i >= 0 && my_board[j].at(i).get_bomb() == false && my_board[j].at(i).get_revealed() == false){
        my_board[j].at(i).reveal_cell();
        if(my_board[j].at(i).get_bomb_number() == 0){
            reveal_cell(j+1, i-1);
            reveal_cell(j+1, i);
            reveal_cell(j+1, i+1);
            reveal_cell(j, i-1);
            reveal_cell(j, i+1);
            reveal_cell(j-1, i-1);
            reveal_cell(j-1, i);
            reveal_cell(j-1, i+1);
        }
    }
}

bool Gameboard::toggle_flagged(size_t j, size_t i, int n_flags){
    if(my_board[j].at(i).get_revealed() == false && n_flags > 0){
        my_board[j].at(i).toggle_flagged();
        return true;
    }
    return false;
}

void Gameboard::reveal_all(){
    for(int j=0; j<10; j++){
        for(int i=0; i<10; i++){
            my_board[j].at(i).reveal_cell();
        }
    }
}