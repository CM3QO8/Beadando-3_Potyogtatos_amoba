#include "GridWidget.hpp"

GridWidget::GridWidget(int x, int y, int width, int height, int cols, int rows)
    : Widget(x, y, width, height), cols(cols), rows(rows) {}

void GridWidget::handle(genv::event ev) {
}

void draw_circle(int center_x, int center_y, int radius) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x*x + y*y <= radius*radius) {
                genv::gout << genv::move_to(center_x + x, center_y + y) << genv::dot;
            }
        }
    }
}

void GridWidget::draw() {
    int cell_width = width / cols;
    int cell_height = height / rows;

    genv::gout << genv::move_to(x, y) << genv::color(0, 0, 255) << genv::box(width, height);

    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            int center_x = x + i * cell_width + cell_width / 2;
            int center_y = y + j * cell_height + cell_height / 2;
            int radius = std::min(cell_width, cell_height) / 3;

            genv::gout << genv::color(255, 255, 255);
            draw_circle(center_x, center_y, radius);
        }
    }
}
