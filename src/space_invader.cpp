#include <iostream>
#include <tuple>

#include "constant.h"
#include "space_invader.h"


using namespace std;

GameLoop::GameLoop() {
    board = new int*[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        board[i] = new int[BOARD_SIZE];
    }

    //Aliens
    for (int i = 0; i < BOARD_SIZE/2; ++i)
    {
        for (int j = 0; j < 2*BOARD_SIZE/3; ++j)
        {
            board[i][j] = ALIEN;
        }
    }

    //Shields
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (i & 1) continue;
        board[BOARD_SIZE - 3][i] = SHIELD;
    }

    //Player
    board[BOARD_SIZE - 1][BOARD_SIZE /2] = PLAYER;


    health = 3; // If hit 3 times then game ends
    pos = BOARD_SIZE/2;
    score = 0;
};

void GameLoop::Fire() {
    // Goes up the matrix and find first impact
    int casualty = 0;
    tuple <int, int> position = make_tuple(0,0);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (board[pos][i] != 0) {
            casualty = board[pos][i];
            get<0>(position) = pos;
            get<1>(position) = i;
            break;
        }
    }

    //Matches the casualty, updates board
    switch(casualty) {
        case ALIEN:
            board[get<0>(position)][get<1>(position)] = EMPTY;
            score += 100;
            break;
        case SHIELD:
            board[get<0>(position)][get<1>(position)] = EMPTY;
            break;
    }       


    //Updates the score


};

void GameLoop::DrawBoard() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << to_string(board[i][j]) << " ";
        }
        cout << "\n";
    }
    cout << endl;
}

int GameLoop::NextRound() {

    // Check last row if there is an alien there
    for (int j = 0; j < BOARD_SIZE; ++j) {
        if (board[BOARD_SIZE - 2][j] == 1) {
            EndGame();
            return 1;
        }
        break;
    }
    
    bool shift_right = false;
    //Iterate through last column
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (board[BOARD_SIZE - 1][i] != 1) {
            shift_right = true;
        }
    } 

    //Shift right
    //Shift down
    //Bottom to top. Don't inclued player row [last row]
    //No need to iterate through first row
    if (shift_right) {
         for (int i = BOARD_SIZE - 1; i >= 0 ; --i) {
            for (int j = BOARD_SIZE - 1; j > 0; --j) {
                board[i][j] = board[i][j - 1];
                board[i][j - 1] = 0;
            }
         }
    } else {
        for (int i = BOARD_SIZE - 2; i > 0; --i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board[i][j] = board[i - 1][j];
                board[i - 1][j] = 0;
            }
        }
    }
    return 0;
}

void GameLoop::EndGame() {
    cout << "You Lose" << endl;
}