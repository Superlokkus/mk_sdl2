#include <mk_sdl2/sdl2_vulcan_helper.hpp>

#include <mk_sdl2/sdl2_helpers.hpp>

#include <SDL_vulkan.h>
#include <SDL.h>

namespace mk {

struct sdl2_vulcan_helper::impl {
    SDL_Window *mainwindow{nullptr};
    const Uint32 sdl_init_flags = SDL_INIT_VIDEO;
};

sdl2_vulcan_helper::sdl2_vulcan_helper() : pimpl(std::make_unique<impl>()) {
    if (!SDL_WasInit(this->pimpl->sdl_init_flags)) {
        if (SDL_Init(this->pimpl->sdl_init_flags) != 0)
            throw sdl2_error("Unable to initialize SDL");
        if (SDL_InitSubSystem(this->pimpl->sdl_init_flags) != 0)
            throw sdl2_error("Unable to initialize sub system of SDL");
    }

    this->pimpl->mainwindow = SDL_CreateWindow("testsdl2_vulcan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                               800, 600,
                                               SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    if (!this->pimpl->mainwindow) {
        SDL_QuitSubSystem(this->pimpl->sdl_init_flags);
        throw sdl2_error("Unable to create window");
    }
}

sdl2_vulcan_helper::~sdl2_vulcan_helper() {
    SDL_DestroyWindow(this->pimpl->mainwindow);
    SDL_QuitSubSystem(this->pimpl->sdl_init_flags);
}

void sdl2_vulcan_helper::redraw(void) {

}

}
