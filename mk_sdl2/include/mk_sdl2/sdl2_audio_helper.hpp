#ifndef CG1_S70357_2017_SDL2_AUDIO_HELPER_HPP
#define CG1_S70357_2017_SDL2_AUDIO_HELPER_HPP

#include <memory>
#include <string_view>

namespace mk {

class sdl2_audio_helper final {
public:
    sdl2_audio_helper();

    ~sdl2_audio_helper();

    void play_wave(const std::string_view &path);

private:
    struct impl;
    std::unique_ptr<impl> pimpl;
};

}
#endif //CG1_S70357_2017_SDL2_AUDIO_HELPER_HPP
