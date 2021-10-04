#include "sdl2_audio_helper.hpp"

#include <utility>

#include <SDL.h>
#include <SDL_audio.h>

#include "sdl2_helpers.hpp"

namespace mk {

struct sdl2_audio_helper::impl {
    const Uint32 sdl_init_flags = SDL_INIT_AUDIO;
};

sdl2_audio_helper::sdl2_audio_helper() : pimpl(std::make_unique<impl>()) {
    if (!SDL_WasInit(this->pimpl->sdl_init_flags)) {
        if (SDL_Init(this->pimpl->sdl_init_flags) != 0)
            throw sdl2_error("Unable to initialize audio SDL");
    }
}

sdl2_audio_helper::~sdl2_audio_helper() {
    SDL_QuitSubSystem(this->pimpl->sdl_init_flags);
}

}
