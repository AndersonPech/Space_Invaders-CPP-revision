#include <iostream>
#include <unistd.h>  
#include "space_invader.h"

#include <condition_variable> 
#include <iostream> 
#include <mutex> 
#include <thread> 

using namespace std;
condition_variable cv;
mutex m;
GameLoop game = GameLoop();
bool ready = true;
void user_input();

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




void nextGame() {
    while(1) {
        sleep(1);
        unique_lock lk(m);
        cv.wait(lk, [] { return ready; });
        if (game.NextRound()) return;
        game.DrawBoard();
    }
}

void userInput() {
    string input = "0";
    PlayerMovement movement;
    while(EOF) {
        input = getchar(); 
        lock_guard lck(m);
        ready = false;
        if (input == "a") {
            movement = PlayerMovement::playerLeft;
            game.MovePlayer(movement);
        } else if (input == "d") {
            movement = PlayerMovement::playerRight;
            game.MovePlayer(movement);
        } else if (input == " ") {
            movement = PlayerMovement::shoot;
            game.MovePlayer(movement);
        } 
        ready = true;
        cv.notify_all();       
    }
    return;
}

int main()
{
    //Initialise Game
    game.ShiftRight();
    game.DrawBoard();


    thread t1 (nextGame);
    thread t2 (userInput);


    t1.join();
    t2.join();   


    t1.detach();
    t2.detach();

    //Game Loop

    return 0;
}