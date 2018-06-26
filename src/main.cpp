#include <iostream>

#include <sdl2_opengl_helper.hpp>
#include <opengl_helper.hpp>
#include "exercises.hpp"
#include <cstdlib>

int main() {
    mk::sdl2_cerr cerr{};
    try {
        mk::sdl2_opengl_helper sdl_opengl_helper{3, 3};
        mk::sdl2_event_helper event_helper{};
        mk::sdl2_cout cout{};
        mk::opengl_helper opengl_helper{};
        {
            exercises::praktikum01_1 ex{};
            exercises::praktikum01_2 ex2{};
            mk::opengl_helper::opengl_program program{};
            program.attach_shaders(ex.shaders());
            program.set_as_current_program();
            ex2.draw();
            sdl_opengl_helper.redraw();
            ex2.draw();
        }

        event_helper.replace_event_handler(std::bind(&mk::sdl2_opengl_helper::redraw, std::ref(sdl_opengl_helper)));
        event_helper.replace_quit_handler([&cout]() {
            cout << "Quiting!\n";
            std::exit(EXIT_SUCCESS);
        });
        while (true)
            event_helper.update_ui();
    } catch (const std::exception &e) {
        cerr << "Exception main: " << e.what() << "\n";
        throw;
    }
}