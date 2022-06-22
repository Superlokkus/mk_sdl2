#ifndef TEST_SDL2_SDL2_2D_RENDER_HELPER_HPP
#define TEST_SDL2_SDL2_2D_RENDER_HELPER_HPP

#include <memory>
#include <optional>

namespace mk {

class sdl2_2d_render_helper final {
public:
    struct window_options_t {
        std::uint32_t width{800};
        std::uint32_t height{600};
        std::optional<float> scale_x;
        std::optional<float> scale_y;
    };

    struct pixel_color_t {
        std::uint8_t red{};
        std::uint8_t green{};
        std::uint8_t blue{};
        std::uint8_t alpha{0};
    };

    void draw_pixel(const pixel_color_t &, const std::uint32_t &x, const std::uint32_t &y);

    sdl2_2d_render_helper(window_options_t);

    ~sdl2_2d_render_helper();

private:
    struct impl;
    std::unique_ptr<impl> pimpl;
};
}
#endif //TEST_SDL2_SDL2_2D_RENDER_HELPER_HPP
