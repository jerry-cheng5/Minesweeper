#include "Gameboard.h"
#include "Cell.h"
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

//Function prototypes

    //Outer Stuff
    void run();
    void print_intro();
    char get_selection();
    void wrapper(char selection);

    //Inner Workings of Game
    void play();
    char get_play();
    int get_coords();

    //Other Options
    void print_rules();
    void print_score();
    void quit();
    void unknown();

//Scorekeeping
    int wins = 0;
    int losses = 0;

//Main
int main(){
    char selection;
    run();
    return 0;
}

//Outer Functions
void run(){
    char selection;
    do{
        print_intro();
        selection = get_selection();
        wrapper(selection);
    }while(selection != 'Q');
}


void print_intro(){
    cout << "\n===================================================" << endl;
    cout << "\nWelcome to my Minesweeper game!" << endl;
    cout << "Please select one of the following choices:" << endl;
    cout << "P - Play\nR - Rules\nS - Score\nQ - Quit" << endl;
}

char get_selection(){
    char selection;
    cin >> selection;
    return toupper(selection);
}

void wrapper(char selection){
    if(selection == 'P')
        play();
    else if(selection == 'R')
        print_rules();
    else if(selection == 'S')
        print_score();
    else if(selection == 'Q')
        quit();
    else
        unknown();
}

//The game
void play(){
    //Create board
    Gameboard my_board;
    my_board.init_bombs(10);

    //Initializing Variables
    bool end_game = false;
    int n_flags = 10;


    //Intro to game
    cout << "\n===================================================" << endl;
    my_board.display_board(n_flags);

    do{
        cout << "\nPlease select one of the following choices:" << endl;
        cout << "S - Select cell\nF - Toggle flag" << endl;
        char player_choice = get_play();
        cout << player_choice << endl;
        cout << "\nPlease enter the row number:" << endl;
        int j = get_coords();
        cout << "\nPlease enter the column number:" << endl;
        int i = get_coords();

        if(player_choice == 'S'){
            if(my_board.get_cell(j, i).get_bomb() == false){
                my_board.reveal_cell(j, i);
            }
            else if(my_board.get_cell(j, i).get_bomb() == true){
                my_board.reveal_bombs();
                end_game = true;
            }
        }
        else if(player_choice == 'F'){
            if(my_board.toggle_flagged(j, i, n_flags) == false)
                cout << "That cell is already revealed, or you have run out of flags" << endl;
            else
                n_flags--;
        }

        my_board.display_board(n_flags);

        if(end_game == true){
            cout << "\nYou lose. Better luck next time!" << endl;
            losses++;
        }
        else if(end_game == false && my_board.check_win() == true){
            end_game = true;
            cout << "\nYou win!" << endl;
            wins++;
        }
    }while(end_game == false);
}

char get_play(){
    char player_choice;
    cin >> player_choice;
    if(toupper(player_choice) != 'S' && toupper(player_choice) != 'F')
        unknown();

    return toupper(player_choice);
}

int get_coords(){
    int coord;
    cin >> coord;
    if(coord < 0 || coord > 9)
        unknown();
    
    return coord;
}

//Other Options
void print_rules(){
    cout << "\n===================================================" << endl;
    cout << "\nRules:" << endl;
    cout << "\nTo win, you have to reveal all the tiles except the ones with bombs. You can determine if the tile is a bomb with the numbers on the adjacent tiles. ";
    cout << "These numbers represent the number of bombs that tile is touching. Diagonally touching counts as touching. ";
    cout << "There are 10 bombs in total, and therefore you have 10 flags so you can mark where you think the bombs are." << endl;
    cout << "\nHave fun!" << endl;

void print_score(){
    cout << "\nThe score is:" << endl;
    cout << wins << " wins" << endl;
    cout << losses << " losses" << endl;
}

void quit(){
    cout << "\nPlease come again!" << endl;
}

void unknown(){
    cout << "\nUnknown selection, please try again:" << endl;
}