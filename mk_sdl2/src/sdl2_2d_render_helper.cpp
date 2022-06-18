#include <mk_sdl2/sdl2_2d_render_helper.hpp>

#include <SDL_render.h>
#include <SDL.h>

#include <mk_sdl2/sdl2_helpers.hpp>

namespace mk {

struct sdl2_2d_render_helper::impl {
    SDL_Window *window{};
    SDL_Renderer *renderer{};

    const Uint32 sdl_init_flags = SDL_INIT_VIDEO;
};

sdl2_2d_render_helper::sdl2_2d_render_helper() : pimpl(std::make_unique<impl>()) {
    if (!SDL_WasInit(this->pimpl->sdl_init_flags)) {
        if (SDL_InitSubSystem(this->pimpl->sdl_init_flags) != 0)
            throw sdl2_error("Unable to initialize sub system of SDL");
    }
    Uint32 window_flags{};
    if (SDL_CreateWindowAndRenderer(800, 600, window_flags,
                                    &this->pimpl->window, &this->pimpl->renderer) != 0)
        throw sdl2_error("Unable to create Window and Renderer");

}

sdl2_2d_render_helper::~sdl2_2d_render_helper() {
    SDL_DestroyRenderer(this->pimpl->renderer);
    SDL_DestroyWindow(this->pimpl->window);
    SDL_QuitSubSystem(this->pimpl->sdl_init_flags);
}
}
