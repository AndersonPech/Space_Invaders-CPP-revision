#include <iostream>
#include "space_invader.h"

using namespace std;


/**
 * @brief Simple Invader Game
 *  Stage 1: 
 *          - Mechanics. Board moves down. Timer is activated. 
 *          - Aliens/ Empty / Shield and Player
 *          - Firing mechanics. No animation but alien/ shield needs to become empty
 *          - Basic input and keybindings
 *  Stage 2: 
 *          - Firing animation
 *          - Score
 *          - End game 
 *  Stage 3:
 *          - Record max score
 *          - Aliens move side to side
 *          
 */
int main()
{
    //Initialise Game
    GameLoop game = GameLoop();
    game.ShiftRight();
    game.DrawBoard();

    //Draw Board

    string input = "0";
    PlayerMovement movement;
    while(EOF) {
        cin >> input;
        if (input == "f") {
            game.NextRound();
        } else if (input == "a") {
            movement = PlayerMovement::playerLeft;
            game.MovePlayer(movement);
        } else if (input == "d") {
            movement = PlayerMovement::playerRight;
            game.MovePlayer(movement);
        } else if (input ==  "w") {
            movement = PlayerMovement::shoot;
            game.MovePlayer(movement);
        }

        game.DrawBoard();
    }


    //Game Loop

    return 0;
}