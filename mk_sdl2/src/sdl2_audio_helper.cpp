#include <mk_sdl2/sdl2_audio_helper.hpp>

#include <utility>

#include <SDL.h>
#include <SDL_audio.h>

#include <mk_sdl2/sdl2_helpers.hpp>

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

void sdl2_audio_helper::play_wave(const std::string_view &path) {
    SDL_AudioSpec spec{};
    Uint8 *audio_buf{};
    Uint32 audio_len{};
    if (SDL_LoadWAV(path.data(), &spec, &audio_buf, &audio_len) == NULL) {
        throw sdl2_error("Unable to open wav");
    }

    SDL_AudioSpec ob_spec{};
    auto device = SDL_OpenAudioDevice(NULL, 0, &spec, &ob_spec, SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (!device) {
        throw sdl2_error("Can not open audio device");
    }
    if (SDL_QueueAudio(device, audio_buf, audio_len)) {
        throw sdl2_error("Can not queue audio");
    }
    SDL_PauseAudioDevice(device, 0);

    //SDL_CloseAudioDevice(device);
    //SDL_FreeWAV(audio_buf);
}

}
