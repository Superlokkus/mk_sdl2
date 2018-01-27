#include <iostream>

#include "sdl2_helper.hpp"


int main() {
    try {
        mk::sdl2_helper{3, 3};
    } catch (const std::exception &e) {
        std::cerr << "Exception main: " << e.what() << std::endl;
        throw;
    }
}