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
        int pos; 
        int health;
        int score;  // alien = 100 points
        int x_pos;

        GameLoop();
        ~GameLoop();

        /**
         * @brief 
         *  Detects if firing from position hits any targets
         */
        void Fire();


        /**
         * @brief 
         * Draws the board
         */
        void DrawBoard();

        /**
         * @brief 
         * Resets the board. Resets all variables
         */
        void ResetBoard();

        /**
         * @brief 
         * Enemy Attacks. Randomise area to attack (within limit of player)
         */
        void EnemyAttack();

        /**
         * @brief 
         * Update board.
         * Check if all enemy is killed and ends game
         * Check if enemy has reached the bottom board
         */
        int NextRound();

        /**
         * @brief 
         * Ends the game
         */
        void EndGame();
};

#endif