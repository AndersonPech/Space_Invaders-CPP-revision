#include <iostream>
#include <tuple>

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

    counter = 0;
    health = 3; // If hit 3 times then game ends
    pos = BOARD_SIZE/2;
    score = 0;
    direct = direction::right;
};

GameLoop::~GameLoop() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        delete[] board[i];
    }

    delete[] board;
}

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

void GameLoop::ShiftDown() {
    for (int i = BOARD_SIZE - 1; i > 0; --i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if ((board[i][j] == 2 && board[i - 1][j] != 1) || board[i - 1][j] == 2) continue;
            if ((board[i][j] == 3 && board[i - 1][j] != 1) || board[i - 1][j] == 3) continue;
            board[i][j] = board[i - 1][j];
            board[i - 1][j] = 0;
        }
    }
}


void GameLoop::ShiftLeft() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE - 1; ++j) {
            if (board[i][j + 1] == 2 || board[i][j] == 2) continue;
            if (board[i][j + 1] == 3 || board[i][j] == 3) continue;
            board[i][j] = board[i][j + 1];
            board[i][j + 1] = 0;
        }
    }
}

void GameLoop::ShiftRight() {
    for (int i = BOARD_SIZE - 1; i >= 0 ; --i) {
        for (int j = BOARD_SIZE - 1; j > 0; --j) {
            if (board[i][j - 1] == 2 || board[i][j] == 2) continue;
            if (board[i][j - 1] == 3 || board[i][j] == 3) continue;
            board[i][j] = board[i][j - 1];
            board[i][j - 1] = 0;
        }
    }
}


int GameLoop::NextRound() {
    // Check second last row if there is an alien there
    for (int j = 0; j < BOARD_SIZE; ++j) {
        if (board[BOARD_SIZE - 1][j] == 1) {
            EndGame();
            return 1;
        }
        break;
    }
    
   
    //Iterate through last column
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (board[i][BOARD_SIZE - 1] == 1) {
            ShiftDown();
            ShiftLeft();
            direct = direction::left;
            return 0;
        }
    } 

    //Iterate through first column
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (board[i][0] == 1) {
            ShiftDown();
            ShiftRight();
            direct = direction::right;
            return 0;
        }
    } 

    if (direct == direction::right) {
        ShiftRight();
    } else {
        ShiftLeft();
    }

    return 0;
}

void GameLoop::EndGame() {
    cout << "You Lose" << endl;
}
