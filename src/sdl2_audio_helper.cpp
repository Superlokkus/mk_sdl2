#include "sdl2_audio_helper.hpp"

#include <utility>

namespace mk {

struct sdl2_audio_helper::impl {

};

sdl2_audio_helper::sdl2_audio_helper() : pimpl(std::make_unique<impl>()) {

}

sdl2_audio_helper::~sdl2_audio_helper() {

}

}
