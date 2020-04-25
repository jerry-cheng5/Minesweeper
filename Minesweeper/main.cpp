#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h>
#include "src/Gameboard.h"
#include "src/Cell.h"
using namespace sf;

//Function Prototypes
void increase_bomb_number(int j, int i, std::vector <std::vector <Cell> > *my_board);
void reveal(int j, int i, std::vector <std::vector <Cell> > *my_board);
void reveal_bombs(std::vector <std::vector <Cell> > *my_board);
void toggle_flagged(int j, int i, std::vector <std::vector <Cell> > *my_board);

int main(){
    //Creating a window
    RenderWindow window(VideoMode(600, 600), "Minesweeper");
    window.setFramerateLimit(60);
    
    //Creating sprite using texture
    Texture t;
    if (!t.loadFromFile("images/tiles.jpg"))
        std::cout << "Error tiles.jpg not found." << std::endl;
    Sprite tile;
    tile.setTexture(t);
    
    //Initializing variables
    int w = 32;
    
    //Creating board
    std::vector <std::vector <Cell> > my_board;
    for(int j=0; j<10; j++){
        my_board.push_back(std::vector<Cell>());
        for(int i=0; i<10; i++){
            my_board[j].push_back(Cell());
        }
    }
    
    //Initializing Bombs and Bomb numbers
    srand (time(NULL));
    int counter = 0;
    while(counter < 10){
        int j = rand() % 10;
        int i = rand() % 10;

        if(my_board[j].at(i).get_bomb() == false){
            my_board[j].at(i).set_bomb();

            increase_bomb_number(j+1, i-1, &my_board);
            increase_bomb_number(j+1, i, &my_board);
            increase_bomb_number(j+1, i+1, &my_board);
            increase_bomb_number(j, i-1, &my_board);
            increase_bomb_number(j, i+1, &my_board);
            increase_bomb_number(j-1, i-1, &my_board);
            increase_bomb_number(j-1, i, &my_board);
            increase_bomb_number(j-1, i+1, &my_board);

            counter++;
        }
    }

    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed) 
                window.close();
            if(Mouse::isButtonPressed(sf::Mouse::Left)){
                Vector2i mouse_pos = sf::Mouse::getPosition(window);
                int i = (mouse_pos.x)/w;
                int j = (mouse_pos.y)/w;
                if((my_board)[j].at(i).get_flagged() == false){
                    if(my_board[j].at(i).get_bomb() == false)
                        reveal(j, i, &my_board);
                    else if(my_board[j].at(i).get_bomb() == true)
                        reveal_bombs(&my_board);
                }
            }
            if(Mouse::isButtonPressed(sf::Mouse::Right)){
                Vector2i mouse_pos = sf::Mouse::getPosition(window);
                int i = (mouse_pos.x)/w;
                int j = (mouse_pos.y)/w;
                toggle_flagged(j, i, &my_board);
            }
        }
        
        window.clear(Color::White);
        
        for(int j=0; j<10; j++){
            for(int i=0; i<10; i++){
                if(my_board[j].at(i).get_revealed() == true){
                    tile.setTextureRect(IntRect(my_board[j].at(i).get_bomb_number()*w,0,w,w));
                    tile.setPosition(i*w, j*w);
                    window.draw(tile);
                }
                else if(my_board[j].at(i).get_flagged() == true){
                    tile.setTextureRect(IntRect(11*w,0,w,w));
                    tile.setPosition(i*w, j*w);
                    window.draw(tile);
                }
                else{
                    tile.setTextureRect(IntRect(10*w,0,w,w));
                    tile.setPosition(i*w, j*w);
                    window.draw(tile);
                }
            }
        }
        
        window.display();
    }
}

void increase_bomb_number(int j, int i, std::vector <std::vector <Cell> > *my_board){
    if(j < 10 && j >= 0 && i < 10 && i >= 0 && (*my_board)[j].at(i).get_bomb() == false){
        (*my_board)[j].at(i).set_bomb_number();
    }
}

void reveal(int j, int i, std::vector <std::vector <Cell> > *my_board){
    if(j < 10 && j >= 0 && i < 10 && i >= 0 && (*my_board)[j].at(i).get_bomb() == false && (*my_board)[j].at(i).get_revealed() == false){
        (*my_board)[j].at(i).reveal_cell();
        if((*my_board)[j].at(i).get_bomb_number() == 0){
            reveal(j+1, i-1, my_board);
            reveal(j+1, i, my_board);
            reveal(j+1, i+1, my_board);
            reveal(j, i-1, my_board);
            reveal(j, i+1, my_board);
            reveal(j-1, i-1, my_board);
            reveal(j-1, i, my_board);
            reveal(j-1, i+1, my_board);
        }
    }
}

void reveal_bombs(std::vector <std::vector <Cell> > *my_board){
    for(int j=0; j<10; j++){
        for(int i=0; i<10; i++){
            if((*my_board)[j].at(i).get_bomb() == true)
                (*my_board)[j].at(i).reveal_cell();
        }
    }
}

void toggle_flagged(int j, int i, std::vector <std::vector <Cell> > *my_board){
    if((*my_board)[j].at(i).get_revealed() == false){
        if((*my_board)[j].at(i).get_flagged() == false)
            (*my_board)[j].at(i).flag();
        else
            (*my_board)[j].at(i).deflag();
    }
}