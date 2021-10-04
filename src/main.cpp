#include <iostream>

#include <mk_sdl2/sdl2_opengl_helper.hpp>
#include <mk_sdl2/sdl2_helpers.hpp>
#include <mk_sdl2/sdl2_audio_helper.hpp>

#include <cstdlib>

int main() {
    mk::sdl2_cerr cerr{};
    try {
        mk::sdl2_opengl_helper sdl_opengl_helper{3, 3};
        mk::sdl2_event_helper event_helper{};
        mk::sdl2_audio_helper audio_helper{};
        mk::sdl2_cout cout{};

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