#include <mk_sdl2/sdl2_2d_render_helper.hpp>

#include <SDL_render.h>
#include <SDL.h>

#include <mk_sdl2/sdl2_helpers.hpp>

namespace mk {

struct sdl2_2d_render_helper::impl {
    window_options_t window_options;
    SDL_Window *window{};
    SDL_Renderer *renderer{};

    const Uint32 sdl_init_flags = SDL_INIT_VIDEO;
};

sdl2_2d_render_helper::sdl2_2d_render_helper(window_options_t window_options
) : pimpl(std::make_unique<impl>(impl{
        .window_options{std::move(window_options)}})) {
    if (!SDL_WasInit(this->pimpl->sdl_init_flags)) {
        if (SDL_InitSubSystem(this->pimpl->sdl_init_flags) != 0)
            throw sdl2_error("Unable to initialize sub system of SDL");
    }
    Uint32 window_flags{};
    if (SDL_CreateWindowAndRenderer(window_options.width * window_options.scale_x.value_or(1),
                                    window_options.height * window_options.scale_y.value_or(1),
                                    window_flags,
                                    &this->pimpl->window, &this->pimpl->renderer) != 0)
        throw sdl2_error("Unable to create Window and Renderer");
    if (window_options.scale_x || window_options.scale_y) {
        if (SDL_RenderSetLogicalSize(this->pimpl->renderer, window_options.width,
                                     window_options.height) != 0)
            throw sdl2_error("Unable Scale Renderer");
    }

}

void
sdl2_2d_render_helper::draw_pixel(const sdl2_2d_render_helper::pixel_color_t &color, const uint32_t &x,
                                  const uint32_t &y) {
    if (SDL_SetRenderDrawColor(this->pimpl->renderer,
                               color.red, color.green, color.blue, color.alpha) != 0) [[unlikely]] {
        throw sdl2_error("Unable to SDL_SetRenderDrawColor");
    }
    if (SDL_RenderDrawPoint(this->pimpl->renderer, x, y) != 0) [[unlikely]] {
        throw sdl2_error("Unable to SDL_RenderDrawPoint");
    }
}

sdl2_2d_render_helper::~sdl2_2d_render_helper() {
    SDL_DestroyRenderer(this->pimpl->renderer);
    SDL_DestroyWindow(this->pimpl->window);
    SDL_QuitSubSystem(this->pimpl->sdl_init_flags);
}
}
