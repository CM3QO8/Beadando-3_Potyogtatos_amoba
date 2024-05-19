#include <graphics.hpp>
#include "GridWidget.hpp"
#include <vector>

int main() {
    genv::gout.open(700, 600);

    GridWidget gridWidget(0, 0, 700, 600, 7, 6);

    std::vector<Widget*> widgets = {&gridWidget};

    genv::event ev;
    while (genv::gin >> ev) {
        for (Widget* w : widgets) {
            w->handle(ev);
        }

        genv::gout << genv::color(0, 0, 0) << genv::box(700, 600);
        for (Widget* w : widgets) {
            w->draw();
        }
        genv::gout << genv::refresh;
    }

    return 0;
}
