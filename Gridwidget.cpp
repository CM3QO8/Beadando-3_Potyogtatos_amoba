#include "GridWidget.hpp"

GridWidget::GridWidget(int x, int y, int width, int height, int cols, int rows)
    : Widget(x, y, width, height), cols(cols), rows(rows), jatekMester(cols, rows), selectedCol(0) {}

void GridWidget::handle(genv::event ev) {
    if (ev.type == genv::ev_key && !jatekMester.isGameOver()) {
        if (ev.keycode == genv::key_left && selectedCol > 0) {
            selectedCol--;
        } else if (ev.keycode == genv::key_right && selectedCol < cols - 1) {
            selectedCol++;
        } else if (ev.keycode == genv::key_space) {
            if (jatekMester.dropDisk(selectedCol) && jatekMester.checkWin()) {
                // Nyerés vagy döntetlen esetén a jatekMester automatikusan frissíti az állapotot
            }
        }
    } else if (ev.type == genv::ev_key && jatekMester.isGameOver() && ev.keycode == genv::key_space) {
        jatekMester.resetGame();
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

    const auto& grid = jatekMester.getGrid();
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

    int selected_center_x = x + selectedCol * cell_width + cell_width / 2;
    genv::gout << genv::move_to(selected_center_x, y) << genv::color(0, 255, 0) << genv::line_to(selected_center_x, y + height);

    if (jatekMester.isGameOver()) {
        genv::gout << genv::color(0, 0, 0) << genv::move_to(0, 0) << genv::box(width, height);
        genv::gout << genv::color(255, 255, 255)
                   << genv::move_to(width / 2 - 50, height / 2 - 10)
                   << genv::text("Piros (Gép) nyert: " + std::to_string(jatekMester.getRedWins()) + "x");
        genv::gout << genv::move_to(width / 2 - 50, height / 2 + 10)
                   << genv::text("Sárga (Játékos) nyert: " + std::to_string(jatekMester.getYellowWins()) + "x");
    }
}
