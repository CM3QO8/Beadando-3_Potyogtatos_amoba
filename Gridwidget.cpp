#include "GridWidget.hpp"

GridWidget::GridWidget(int x, int y, int width, int height, int cols, int rows)
    : Widget(x, y, width, height), cols(cols), rows(rows), currentPlayer(1), selectedCol(0) {
    grid.resize(cols, std::vector<int>(rows, 0));
}

void GridWidget::handle(genv::event ev) {
    if (ev.type == genv::ev_key) {
        if (ev.keycode == genv::key_left && selectedCol > 0) {
            selectedCol--;
        } else if (ev.keycode == genv::key_right && selectedCol < cols - 1) {
            selectedCol++;
        } else if (ev.keycode == genv::key_space) {
            dropDisk();
        }
    }
}

void GridWidget::dropDisk() {
    for (int row = rows - 1; row >= 0; row--) {
        if (grid[selectedCol][row] == 0) {
            grid[selectedCol][row] = currentPlayer;
            currentPlayer = (currentPlayer == 1) ? 2 : 1; // Játékos váltás
            break;
        }
    }
}

void draw_circle(int center_x, int center_y, int radius, int r, int g, int b) {
    genv::gout << genv::color(r, g, b);
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

            int color = grid[i][j];
            if (color == 1) {
                draw_circle(center_x, center_y, radius, 255, 0, 0);
            } else if (color == 2) {
                draw_circle(center_x, center_y, radius, 255, 255, 0);
            } else {
                draw_circle(center_x, center_y, radius, 255, 255, 255);
            }
        }
    }

    // Kijelölt oszlop jelzése
    int selected_center_x = x + selectedCol * cell_width + cell_width / 2;
    genv::gout << genv::move_to(selected_center_x - cell_width / 2, y) << genv::color(255, 255, 255) << genv::line(cell_width, 0);
    genv::gout << genv::move_to(selected_center_x - cell_width / 2, y + height) << genv::color(255, 255, 255) << genv::line(cell_width, 0);
}
