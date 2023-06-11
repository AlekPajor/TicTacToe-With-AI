#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <iostream>

using namespace std;

const int MAX = 10000;
const int MIN = -10000;

typedef vector<vector<char>> brd_type;

class Game {
private:
    const char EMPTY_CELL = ' ';    
    const char PLAYER = 'X';
    const char BOT = 'O';
    vector<vector<vector<int>>> WIN_POS;
    int BOARD_SIZE;
    brd_type BOARD;

    void winBoardGen() {
        // Generate winning rows
        for (int ROW = 0; ROW < BOARD_SIZE; ROW++) {
            vector<vector<int>> pos;
            for(int COL = 0; COL < BOARD_SIZE; COL++) {
            vector<int> index(2);
            index[0] = ROW;
            index[1] = COL;
            pos.push_back(index);
            };
            WIN_POS.push_back(pos);   
        };

        // Generate winning columns
        for (int ROW = 0; ROW < BOARD_SIZE; ROW++) {
            vector<vector<int>> pos;
            for(int COL = 0; COL < BOARD_SIZE; COL++) {
                vector<int> index(2);
                index[0] = COL;
                index[1] = ROW;
                pos.push_back(index);
            };
            WIN_POS.push_back(pos);   
        };

        // Generate 1-st diagonal
        vector<vector<int>> d1pos;
        for(int i = 0 ; i < BOARD_SIZE; i++) {
            vector<int> index(2);
            index[0] = index[1] = i;
            d1pos.push_back(index);
        };
        WIN_POS.push_back(d1pos);

        // Generate 2-nd diagonal
        vector<vector<int>> d2pos;
        for(int i = 0 ; i < BOARD_SIZE; i++) {
            vector<int> index(2);
            index[0] = (BOARD_SIZE - 1) - i;
            index[1] = i;
            d2pos.push_back(index);
        };
        WIN_POS.push_back(d2pos);
    }

    bool isBoardFull() {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (BOARD[i][j] == EMPTY_CELL)
                    return false;
            }
        }
        return true;
    }

public:

    Game(int size) {
        BOARD_SIZE = size;
        BOARD = setBoard(size);
        winBoardGen();
    }

    ~Game() {}

    vector<vector<char>> setBoard(int size) {
        vector<vector<char>> BOARD(size, vector<char>(size, ' '));
        return BOARD;
    }

    bool isGameOver() {
        if (isBoardFull()) {
            cout << "Board full, end" << endl;
            return true;
        }
        else if(evaluate(BOARD, BOT) == MIN) {
            cout << "You won, end" <<  endl;
            return true;
        }
        else if (evaluate(BOARD, BOT) == MAX) {
            cout << "Bot won, end" << endl;
            return true;
        }
        else return false;
    }

    bool isCellEmpty(pair<int, int> pos) {
        if(BOARD[pos.first][pos.second]==EMPTY_CELL)
            return true;
        else return false;
    }

    void printWinPos() {
        // Iterate over the elements of the vector
        for (const auto& dim1 : WIN_POS) {
            for (const auto& dim2 : dim1) {
                for (const auto& element : dim2) {
                    cout << element << " ";
                }
                cout << endl;  // Print a newline after each 2D matrix
            }
            cout << endl;  // Print an additional newline after each 3D layer
        }
    }

    void printBoard() {
        for(int rows = 0; rows < BOARD_SIZE; rows++) {
            for(int cols = 0; cols < BOARD_SIZE; cols++) {
                cout << BOARD[rows][cols];
                if(cols < BOARD_SIZE-1) cout << " | ";
            }
            cout << endl;
            for(int n = 0; n < 3*(BOARD_SIZE-1)+BOARD_SIZE; n++) {
                if(rows<BOARD_SIZE-1) cout<<"-";
            }
            cout << endl;
        }
    }

    void move(pair<int, int> pos, char player) {
        if (pos.first >= 0 && pos.second >= 0 && pos.first < BOARD_SIZE && pos.second < BOARD_SIZE && isCellEmpty(pos)) {
            BOARD[pos.first][pos.second] = player;
        }
    }

    void inputMove() {
        pair<int, int> pos;
        bool valid_move = false;
        do {
            cout << "Where to put? [row][col]" << endl;
            cin >> pos.first >> pos.second;
                pos.first--;
                pos.second--;
        
            if (pos.first >= 0 && pos.first < BOARD_SIZE && pos.second >= 0 && pos.second < BOARD_SIZE && isCellEmpty(pos)) {
                move(pos, 'X');
                valid_move=true;
            }
            else cout << "Wrong move, try again" << endl;
        } while(valid_move == false);
    }

//======================BOT=============================
    int evaluate(brd_type state, char player) {

        //Iterate through all possible wins to check win
        if(player == BOT) {
            for (int i = 0; i < 2*BOARD_SIZE+2; i++) {
                //Check for bots's win
                int isMAX = 0;
                for(int j = 0; j < BOARD_SIZE; j++) {
                    if ((state[WIN_POS[i][j][0]][WIN_POS[i][j][1]] == BOT))
                    {
                        isMAX++;
                    }
                    else break;
                }
                if(isMAX==BOARD_SIZE) {
                    int x;
                    return 10000;
                }
            }

            for (int i = 0; i < 2*BOARD_SIZE+2; i++) {
                //Check for players's win
                int isMIN = 0;
                for(int j =0; j < BOARD_SIZE; j++) {
                    if ((state[WIN_POS[i][j][0]][WIN_POS[i][j][1]] == PLAYER))
                    {
                        isMIN++;
                    }
                    else break;
                }
                if(isMIN==BOARD_SIZE) return -10000;
            }
        }
        else
        {        
            for (int i = 0; i < 2*BOARD_SIZE+2; i++) {
                //Check for players's win
                int isMIN = 0;
                for(int j =0; j < BOARD_SIZE; j++) {
                    if ((state[WIN_POS[i][j][0]][WIN_POS[i][j][1]] == PLAYER))
                    {
                        isMIN++;
                    }
                    else break;
                }
                if(isMIN==BOARD_SIZE) return -10000;
            }
            
            for (int i = 0; i < 2*BOARD_SIZE+2; i++) {
                //Check for bots's win
                int isMAX = 0;
                for(int j = 0; j < BOARD_SIZE; j++) {
                    if ((state[WIN_POS[i][j][0]][WIN_POS[i][j][1]] == BOT))
                    {
                        isMAX++;
                    }
                    else break;
                }
                if(isMAX==BOARD_SIZE) return 10000;
            }
        }
    
        //Iterate through all possible wins to evaluate
        int eval = 0;
        for (int i = 0; i < 2*BOARD_SIZE+2; i++) {
            int isMAX = 0;
            int botBoost = 0;

            for(int j = 0; j < BOARD_SIZE; j++) {
                if ((state[WIN_POS[i][j][0]][WIN_POS[i][j][1]] != PLAYER))
                {
                    if(state[WIN_POS[i][j][0]][WIN_POS[i][j][1]] == BOT) {
                        botBoost++;
                    }
                    isMAX++;
                }
            }
            if(isMAX==BOARD_SIZE) eval = eval + 1; //+botBoost;
            
            int isMIN = 0;
            for(int j =0; j < BOARD_SIZE; j++) {
                if ((state[WIN_POS[i][j][0]][WIN_POS[i][j][1]] != BOT))
                {
                    isMIN++;
                }
            }
            if(isMIN==BOARD_SIZE) eval--;
        }
        return eval;
    }
   
    int minmaxrec(brd_type state, int depth, int a, int b, char player) {
        int value = evaluate(state, player);
        if (depth == 0 || value == MIN || value == MAX)
            return value;

        bool prune = false;
            
        if (player == BOT)
        {
            int maxEval = MIN;
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                for (int j = 0; j < BOARD_SIZE; j++)
                {
                    if (state[i][j] == EMPTY_CELL)
                    {
                        brd_type nextState = state;
                        nextState[i][j] = BOT;
                        
                        int eval = minmaxrec(nextState, depth - 1, a, b, PLAYER);
                        maxEval = max(maxEval, eval);
                        a = max(a, eval);

                        if (b <= a)
                        {
                            prune = true;
                            break;
                        }
                    }
                }
                if (prune) { break; }
            }
            return maxEval;
        }
        else
        {
            int minEval = MAX;
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                for (int j = 0; j < BOARD_SIZE; j++)
                {
                    if (state[i][j] == EMPTY_CELL)
                    {
                        brd_type nextState = state;
                        nextState[i][j] = PLAYER;

                        int eval = minmaxrec(nextState, depth - 1, a, b, BOT);
                        minEval = min(minEval, eval);
                        b = min(b, eval);

                        if (b <= a)
                        {
                            prune = true;
                            break;
                        }
                    }
                }
                if (prune) { break;}
            }
            return minEval;
        }
    }

    pair<int, int> minmax(int depth, char player) {   
        pair<int, int> move;
        if (!(player == 'X' || player == 'O')) {
            move.first = -1;
            move.second = -1;
            return move;
        }

        int value = evaluate(BOARD, player);
        if (depth == 0 || value == MIN || value == MAX) {
            move.first= value;
            move.second= value;
            return move;
        }
        
        if (player == 'O')
        {
            int maxEval = MIN;
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                for (int j = 0; j < BOARD_SIZE; j++)
                {
                    if (BOARD[i][j] == EMPTY_CELL)
                    {
                        brd_type nextState = BOARD;
                        nextState[i][j] = 'O';
                        if(evaluate(nextState, BOT) == MAX){
                            move.first = i;
                            move.second = j;
                            return move;
                        }
                        int eval = minmaxrec(nextState, depth - 1, maxEval, MAX, PLAYER);

                        if (eval > maxEval)
                        {
                            move.first = i;
                            move.second = j;
                            maxEval = eval;
                        }
                    }
                }
            }
        }
        else
        {
            int minEval = MAX;
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                for (int j = 0; j < BOARD_SIZE; j++)
                {
                    if (BOARD[i][j] == EMPTY_CELL)
                    {
                        brd_type nextState = BOARD;
                        nextState[i][j] = 'X';

                        int eval = minmaxrec(nextState, depth - 1, MIN, minEval, BOT);
                        if (eval < minEval)
                        {
                            move.first = i;
                            move.second = j;
                            minEval = eval;
                        }
                    }
                }
            }
        }
        return move;
    }

}; 

#endif