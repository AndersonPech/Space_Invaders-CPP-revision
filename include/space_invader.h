#include "constant.h"

#ifndef GAMELOOP_H
#define GAMELOOP_H

class GameLoop {
    public: 
        // Initialise board
        // 0 = empty
        // 1 = alien
        // 2 = shield 
        // 3 = player
        int **board;
        int health;
        int score;  // alien = 100 points
        int player_position; //Location of player (Make set if need y axis)
        int tick;
        int counter;
        direction direct;

        GameLoop();
        ~GameLoop();

        /**
         * @brief 
         *  Detects if firing from position hits any targets
         */
        void Fire(int pos);


        /**
         * @brief 
         * Draws the board
         */
        void DrawBoard();

        /**
         * @brief 
         * Moves the player
         */
        void MovePlayer(PlayerMovement movement);

        
        /**
         * @brief 
         * Resets the board. Resets all variables
         */
        void ResetBoard();

        /**
         * @brief 
         * Update board.
         * Check if all enemy is killed and ends game
         * Check if enemy has reached the bottom board
         */
        int NextRound();

        /**
         * @brief 
         * Shift Down.
         */
        void ShiftDown();
        
        /**
         * @brief 
         * Shift Left
         */
        void ShiftLeft();

        /**
         * @brief 
         * Shift Right
         */
        void ShiftRight();

        /**
         * @brief 
         * Ends the game
         */
        void EndGame();

        void ShootingAnimation(int position, int impact); 
};

#endif