#ifndef GRIDWIDGET_HPP
#define GRIDWIDGET_HPP

#include "Widget.hpp"
#include <vector>

class GridWidget : public Widget {
private:
    int cols, rows;
    std::vector<std::vector<int>> grid; // 0: �res, 1: piros, 2: s�rga
    int currentPlayer; // 1: piros, 2: s�rga
    int selectedCol;
    std::vector<std::pair<int, int>> winningLine;
    int redWins;
    int yellowWins;
    bool gameOver;

    bool checkLine(int x, int y, int dx, int dy);
    bool checkWin();
    void resetGame();
public:
    GridWidget(int x, int y, int width, int height, int cols, int rows);
    void handle(genv::event ev) override;
    void draw() override;
    void dropDisk();
};

#endif // GRIDWIDGET_HPP
