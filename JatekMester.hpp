#ifndef JATEKMESTER_HPP
#define JATEKMESTER_HPP

#include <vector>

class JatekMester {
private:
    int cols, rows;
    std::vector<std::vector<int>> grid; // 0: üres, 1: piros, 2: sárga
    int currentPlayer; // 1: piros, 2: sárga
    int redWins;
    int yellowWins;
    bool gameOver;
    std::vector<std::pair<int, int>> winningLine;

    bool checkLine(int x, int y, int dx, int dy);
public:
    JatekMester(int cols, int rows);
    void resetGame();
    bool dropDisk(int col);
    bool checkWin();
    bool isGameOver() const;
    std::vector<std::pair<int, int>> getWinningLine() const;
    int getCurrentPlayer() const;
    int getRedWins() const;
    int getYellowWins() const;
    const std::vector<std::vector<int>>& getGrid() const;
};

#endif // JATEKMESTER_HPP
