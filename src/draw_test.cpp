#include <mk_sdl2/sdl2_helpers.hpp>
#include <mk_sdl2/sdl2_2d_render_helper.hpp>

int main() {
    mk::sdl2_cerr cerr{};
    try {
        mk::sdl2_event_helper event_helper{};
        mk::sdl2_2d_render_helper render_helper{{160, 144, 4, 4,
                                                        .window_title{"Draw Test"}}};
        for (int i{}, j{}; j < 100; ++i) {
            render_helper.draw_pixel({std::uint8_t(i * 2), std::uint8_t(255u - i * 2u), 255}, i, j);
            if (i > 100) {
                i = -1;
                ++j;
            }
        }
        render_helper.present_frame();


        mk::sdl2_cout cout{};

        //event_helper.replace_event_handler(std::bind(&mk::sdl2_vulcan_helper::redraw, std::ref(sdl_vulcan_helper)));
        event_helper.replace_quit_handler([&cout]() {
            cout << "Quiting!\n";
            std::exit(0);
        });
        while (true)
            event_helper.update_ui();
    } catch (const std::exception &e) {
        cerr << "Exception main: " << e.what() << "\n";
        throw;
    }
}
