#include <iostream>

#include "sdl2_helper.hpp"
#include "renderer.hpp"


int main() {
    try {
        mk::sdl2_helper helper{3, 3};
        mk::renderer renderer{};
        while (true)helper.redraw();
    } catch (const std::exception &e) {
        std::cerr << "Exception main: " << e.what() << std::endl;
        throw;
    }
}