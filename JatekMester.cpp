#include "JatekMester.hpp"

JatekMester::JatekMester(int cols, int rows)
    : cols(cols), rows(rows), currentPlayer(1), redWins(0), yellowWins(0), gameOver(false) {
    resetGame();
}

void JatekMester::resetGame() {
    grid = std::vector<std::vector<int>>(cols, std::vector<int>(rows, 0));
    currentPlayer = 1;
    winningLine.clear();
    gameOver = false;
}

bool JatekMester::dropDisk(int col) {
    if (gameOver) return false;
    for (int row = rows - 1; row >= 0; --row) {
        if (grid[col][row] == 0) {
            grid[col][row] = currentPlayer;
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
            return true;
        }
    }
    return false;
}

bool JatekMester::checkLine(int x, int y, int dx, int dy) {
    int player = grid[x][y];
    int count = 0;
    std::vector<std::pair<int, int>> line;

    for (int i = 0; i < 4; ++i) {
        int nx = x + i * dx;
        int ny = y + i * dy;
        if (nx >= 0 && nx < cols && ny >= 0 && ny < rows && grid[nx][ny] == player) {
            line.push_back({nx, ny});
            count++;
        } else {
            break;
        }
    }

    if (count == 4) {
        winningLine = line;
        return true;
    }
    return false;
}

bool JatekMester::checkWin() {
    for (int x = 0; x < cols; ++x) {
        for (int y = 0; y < rows; ++y) {
            if (grid[x][y] != 0) {
                if (checkLine(x, y, 1, 0) ||
                    checkLine(x, y, 0, 1) ||
                    checkLine(x, y, 1, 1) ||
                    checkLine(x, y, 1, -1)) {
                    gameOver = true;
                    if (currentPlayer == 1) {
                        yellowWins++;
                    } else {
                        redWins++;
                    }
                    return true;
                }
            }
        }
    }

    for (int x = 0; x < cols; ++x) {
        if (grid[x][0] == 0) {
            return false;
        }
    }

    gameOver = true;
    return true;
}

bool JatekMester::isGameOver() const {
    return gameOver;
}

std::vector<std::pair<int, int>> JatekMester::getWinningLine() const {
    return winningLine;
}

int JatekMester::getCurrentPlayer() const {
    return currentPlayer;
}

int JatekMester::getRedWins() const {
    return redWins;
}

int JatekMester::getYellowWins() const {
    return yellowWins;
}

const std::vector<std::vector<int>>& JatekMester::getGrid() const {
    return grid;
}
