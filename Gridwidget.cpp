#include "GridWidget.hpp"

GridWidget::GridWidget(int x, int y, int width, int height, int cols, int rows)
    : Widget(x, y, width, height), cols(cols), rows(rows), currentPlayer(1), selectedCol(0),
      redWins(0), yellowWins(0), gameOver(false) {
    grid.resize(cols, std::vector<int>(rows, 0));
}

void GridWidget::handle(genv::event ev) {
    if (ev.type == genv::ev_key && !gameOver) {
        if (ev.keycode == genv::key_left && selectedCol > 0) {
            selectedCol--;
        } else if (ev.keycode == genv::key_right && selectedCol < cols - 1) {
            selectedCol++;
        } else if (ev.keycode == genv::key_space) {
            dropDisk();
            if (checkWin()) {
                gameOver = true;
                if (currentPlayer == 1) {
                    yellowWins++;
                } else {
                    redWins++;
                }
            }
        }
    } else if (ev.type == genv::ev_key && gameOver && ev.keycode == genv::key_space) {
        resetGame();
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

bool GridWidget::checkLine(int x, int y, int dx, int dy) {
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

bool GridWidget::checkWin() {
    for (int x = 0; x < cols; ++x) {
        for (int y = 0; y < rows; ++y) {
            if (grid[x][y] != 0) {
                if (checkLine(x, y, 1, 0) ||
                    checkLine(x, y, 0, 1) ||
                    checkLine(x, y, 1, 1) ||
                    checkLine(x, y, 1, -1))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void GridWidget::resetGame() {
    grid.clear();
    grid.resize(cols, std::vector<int>(rows, 0));
    currentPlayer = 1;
    selectedCol = 0;
    winningLine.clear();
    gameOver = false;
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

    int selected_center_x = x + selectedCol * cell_width + cell_width / 2;
    genv::gout << genv::move_to(selected_center_x, y) << genv::color(0, 255, 0) << genv::line_to(selected_center_x, y + height);

    if (!winningLine.empty()) {
        genv::gout << genv::color(0, 255, 0);
        for (size_t i = 0; i < winningLine.size() - 1; ++i) {
            int start_x = x + winningLine[i].first * cell_width + cell_width / 2;
            int start_y = y + winningLine[i].second * cell_height + cell_height / 2;
            int end_x = x + winningLine[i + 1].first * cell_width + cell_width / 2;
            int end_y = y + winningLine[i + 1].second * cell_height + cell_height / 2;
            genv::gout << genv::move_to(start_x, start_y) << genv::line_to(end_x, end_y);
        }
    }

    if (gameOver) {
        genv::gout << genv::color(0, 0, 0) << genv::move_to(0, 0) << genv::box(width, height);
        genv::gout << genv::color(255, 255, 255)
                   << genv::move_to(width / 2 - 50, height / 2 - 10)
                   << genv::text("Piros (Gép) nyert: " + std::to_string(redWins) + "x");
        genv::gout << genv::move_to(width / 2 - 50, height / 2 + 10)
                   << genv::text("Sárga (Játékos) nyert: " + std::to_string(yellowWins) + "x");
    }
}
