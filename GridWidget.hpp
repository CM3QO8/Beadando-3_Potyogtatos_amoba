#ifndef GRIDWIDGET_HPP
#define GRIDWIDGET_HPP

#include "Widget.hpp"
#include "JatekMester.hpp"

class GridWidget : public Widget {
private:
    int cols, rows;
    JatekMester jatekMester;
    int selectedCol;

public:
    GridWidget(int x, int y, int width, int height, int cols, int rows);
    void handle(genv::event ev) override;
    void draw() override;
};

#endif // GRIDWIDGET_HPP
