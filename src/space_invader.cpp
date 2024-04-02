#include <iostream>
#include <tuple>
#include <unistd.h>  
#include <mutex>

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
            num_aliens++;
        }
    }

    //Shields
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (i & 1) continue;
        board[BOARD_SIZE - 3][i] = SHIELD;
    }

    //Player
    board[BOARD_SIZE - 1][BOARD_SIZE /2] = PLAYER;
    player_position = BOARD_SIZE / 2;

    counter = 0;
    health = 3; // If hit 3 times then game ends
    score = 0;
    direct = direction::right;
};

GameLoop::~GameLoop() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

void GameLoop::ShootingAnimation(int position, int impact) {
        int previous = BOARD_SIZE - 2; //Second last row. Skips row of player
        board[previous][position] = FIRE; //Sets it to FIRE
        DrawBoard();
        
        for (int i = BOARD_SIZE - 3; i > impact; --i) {
            board[previous][position] = 0;
            board[i][position] = 4;
            usleep(3000);
            previous = i;
            DrawBoard();
        }

        board[previous][position] = 0;

};

void GameLoop::Fire(int pos) {
    // Goes up the matrix and find first impact
    int casualty = 0;
    tuple <int, int> position = make_tuple(0,0);
    int prev = 0;
    for (int i = BOARD_SIZE - 2; i >= 0; --i) {
        if (board[i][pos] != 0) {
            casualty = board[i][pos];
            get<0>(position) = i;
            get<1>(position) = pos;
            break;
        }
    }

    ShootingAnimation(pos, get<0>(position));

    //Matches the casualty, updates board
    switch(casualty) {
        case ALIEN:
            board[get<0>(position)][get<1>(position)] = EMPTY;
            score += 100;
            aliens_shot++;
            break;
        case SHIELD:
            board[get<0>(position)][get<1>(position)] = EMPTY;
            break;
    }       

    DrawBoard();


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

void GameLoop::MovePlayer(PlayerMovement movement) {
    switch(movement) {
        case(PlayerMovement::playerLeft):
            if (player_position - 1 >= 0) {
                board[BOARD_SIZE - 1][player_position - 1] = PLAYER;
                board[BOARD_SIZE - 1][player_position] = EMPTY;
                player_position = player_position - 1;
            }
            break;
        case(PlayerMovement::playerRight):
            if (player_position + 1 < BOARD_SIZE) {
                board[BOARD_SIZE - 1][player_position + 1] = PLAYER;
                board[BOARD_SIZE - 1][player_position] = EMPTY;
                player_position = player_position + 1;
            }
            break;
        case(PlayerMovement::shoot):
            Fire(player_position);
        default:
            break;
    }    
}


int GameLoop::NextRound() {
    // Check second last row if there is an alien there
    if (aliens_shot == num_aliens) {
        cout << "You've Won!!!";
        return 1;
    }

    for (int j = 0; j < BOARD_SIZE; ++j) {
        if (board[BOARD_SIZE - 1][j] == ALIEN) {
            EndGame();
            return 1;
        }
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
