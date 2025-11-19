#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const char HUMAN = 'X';
const char AI = 'O';
const char EMPTY = ' ';

struct Move {
    int row;
    int col;
};

// Display the current board
void printBoard(const vector<vector<char>>& board) {
    cout << "\n";
    for (int r = 0; r < 3; ++r) {
        cout << " ";
        for (int c = 0; c < 3; ++c) {
            cout << board[r][c];
            if (c < 2) cout << " | ";
        }
        cout << "\n";
        if (r < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

// Check if there are moves left
bool isMovesLeft(const vector<vector<char>>& board) {
    for (auto& row : board)
        for (auto cell : row)
            if (cell == EMPTY) return true;
    return false;
}

// Evaluate the board:
// +10 if AI wins, -10 if HUMAN wins, 0 otherwise
int evaluate(const vector<vector<char>>& b) {
    // Rows
    for (int r = 0; r < 3; ++r) {
        if (b[r][0] == b[r][1] && b[r][1] == b[r][2] && b[r][0] != EMPTY) {
            if (b[r][0] == AI) return +10;
            if (b[r][0] == HUMAN) return -10;
        }
    }
    // Columns
    for (int c = 0; c < 3; ++c) {
        if (b[0][c] == b[1][c] && b[1][c] == b[2][c] && b[0][c] != EMPTY) {
            if (b[0][c] == AI) return +10;
            if (b[0][c] == HUMAN) return -10;
        }
    }
    // Diagonals
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2] && b[0][0] != EMPTY) {
        if (b[0][0] == AI) return +10;
        if (b[0][0] == HUMAN) return -10;
    }
    if (b[0][2] == b[1][1] && b[1][1] == b[2][0] && b[0][2] != EMPTY) {
        if (b[0][2] == AI) return +10;
        if (b[0][2] == HUMAN) return -10;
    }
    return 0;
}

// Minimax with alpha-beta pruning
int minimax(vector<vector<char>>& board, int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(board);

    // Terminal states
    if (score == +10) return score - depth; // prefer faster wins
    if (score == -10) return score + depth; // prefer slower losses
    if (!isMovesLeft(board)) return 0;

    if (isMax) { // AI's turn (maximize)
        int best = numeric_limits<int>::min();
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                if (board[r][c] == EMPTY) {
                    board[r][c] = AI;
                    int val = minimax(board, depth + 1, false, alpha, beta);
                    board[r][c] = EMPTY;
                    best = max(best, val);
                    alpha = max(alpha, best);
                    if (beta <= alpha) return best; // prune
                }
            }
        }
        return best;
    } else { // Human's turn (minimize)
        int best = numeric_limits<int>::max();
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                if (board[r][c] == EMPTY) {
                    board[r][c] = HUMAN;
                    int val = minimax(board, depth + 1, true, alpha, beta);
                    board[r][c] = EMPTY;
                    best = min(best, val);
                    beta = min(beta, best);
                    if (beta <= alpha) return best; // prune
                }
            }
        }
        return best;
    }
}

// Find the best move for AI
Move findBestMove(vector<vector<char>>& board) {
    int bestVal = numeric_limits<int>::min();
    Move bestMove{-1, -1};

    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (board[r][c] == EMPTY) {
                board[r][c] = AI;
                int moveVal = minimax(board, 0, false, numeric_limits<int>::min(), numeric_limits<int>::max());
                board[r][c] = EMPTY;

                if (moveVal > bestVal) {
                    bestMove = {r, c};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

// Check win/draw for messaging
bool hasWinner(const vector<vector<char>>& board, char& winner) {
    // Rows
    for (int r = 0; r < 3; ++r) {
        if (board[r][0] != EMPTY && board[r][0] == board[r][1] && board[r][1] == board[r][2]) {
            winner = board[r][0];
            return true;
        }
    }
    // Columns
    for (int c = 0; c < 3; ++c) {
        if (board[0][c] != EMPTY && board[0][c] == board[1][c] && board[1][c] == board[2][c]) {
            winner = board[0][c];
            return true;
        }
    }
    // Diagonals
    if (board[0][0] != EMPTY && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        winner = board[0][0];
        return true;
    }
    if (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        winner = board[0][2];
        return true;
    }
    return false;
}

// Human move input with validation
bool humanMove(vector<vector<char>>& board) {
    int r, c;
    cout << "Enter your move (row and column: 1-3 1-3): ";
    if (!(cin >> r >> c)) return false; // input error
    r--; c--;
    if (r < 0 || r > 2 || c < 0 || c > 2) {
        cout << "Invalid position. Try again.\n";
        return humanMove(board);
    }
    if (board[r][c] != EMPTY) {
        cout << "Cell already occupied. Try again.\n";
        return humanMove(board);
    }
    board[r][c] = HUMAN;
    return true;
}

int main() {
    cout << "Tic-Tac-Toe (Human: X, AI: O)\n";
    cout << "You play first.\n";

    vector<vector<char>> board(3, vector<char>(3, EMPTY));
    char winner = EMPTY;

    while (true) {
        // Human turn
        printBoard(board);
        if (!humanMove(board)) {
            cout << "Input error. Exiting.\n";
            return 0;
        }

        if (hasWinner(board, winner)) {
            printBoard(board);
            cout << (winner == HUMAN ? "You win!\n" : "AI wins!\n");
            break;
        }
        if (!isMovesLeft(board)) {
            printBoard(board);
            cout << "It's a draw!\n";
            break;
        }

        // AI turn
        Move best = findBestMove(board);
        board[best.row][best.col] = AI;
        cout << "AI plays: (" << best.row + 1 << ", " << best.col + 1 << ")\n";

        if (hasWinner(board, winner)) {
            printBoard(board);
            cout << (winner == HUMAN ? "You win!\n" : "AI wins!\n");
            break;
        }
        if (!isMovesLeft(board)) {
            printBoard(board);
            cout << "It's a draw!\n";
            break;
        }
    }

    cout << "Game over.\n";
    return 0;
}
