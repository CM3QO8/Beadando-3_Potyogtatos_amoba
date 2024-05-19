#ifndef GRIDWIDGET_HPP
#define GRIDWIDGET_HPP

#include "Widget.hpp"
#include <vector>

class GridWidget : public Widget {
private:
    int cols, rows;
    std::vector<std::vector<int>> grid; // 0: üres, 1: piros, 2: sárga
    int currentPlayer; // 1: piros, 2: sárga
    int selectedCol; // Jelenlegi kiválasztott oszlop
public:
    GridWidget(int x, int y, int width, int height, int cols, int rows);
    void handle(genv::event ev) override;
    void draw() override;
    void dropDisk();
};

#endif // GRIDWIDGET_HPP
