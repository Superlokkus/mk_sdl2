#ifndef TEST_SDL2_SDL2_2D_RENDER_HELPER_HPP
#define TEST_SDL2_SDL2_2D_RENDER_HELPER_HPP

#include <memory>

namespace mk {

class sdl2_2d_render_helper final {
public:
    sdl2_2d_render_helper();

    ~sdl2_2d_render_helper();

private:
    struct impl;
    std::unique_ptr<impl> pimpl;
};
}
#endif //TEST_SDL2_SDL2_2D_RENDER_HELPER_HPP
