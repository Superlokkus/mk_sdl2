#include "sdl2_helpers.hpp"

#include <SDL.h>
#include <SDL_events.h>
#include <cstdlib>

namespace mk {

mk::sdl2_error::sdl2_error(const std::string &what) :
        runtime_error(what + " SDL:" + SDL_GetError()) {
    SDL_ClearError();

}

mk::sdl2_error::sdl2_error(const char *what) :
        runtime_error(std::string(what) + " SDL:" + SDL_GetError()) {
    SDL_ClearError();
}

struct mk::sdl2_event_helper::impl {
    const Uint32 sdl_init_flags = SDL_INIT_EVENTS;
    event_handler current_event_handler;
    event_handler current_quit_handler{[]() { std::exit(EXIT_SUCCESS); }};
};

mk::sdl2_event_helper::sdl2_event_helper() :
        impl(new struct impl) {
    if (!SDL_WasInit(this->impl->sdl_init_flags)) {
        if (SDL_Init(this->impl->sdl_init_flags) != 0)
            throw sdl2_error("Unable to initialize SDL");
        if (SDL_InitSubSystem(this->impl->sdl_init_flags) != 0)
            throw sdl2_error("Unable to initialize sub system of SDL");
    }
}

mk::sdl2_event_helper::~sdl2_event_helper() {
    SDL_QuitSubSystem(this->impl->sdl_init_flags);
}

void mk::sdl2_event_helper::update_ui() {
    SDL_Event currentEvent{};
    if (SDL_PollEvent(&currentEvent) == 0)
        return;
    switch (currentEvent.type) {
        case SDL_QUIT:
            this->impl->current_quit_handler();
            break;
        default:
            if (this->impl->current_event_handler)
                this->impl->current_event_handler();
            break;
    }

}

auto mk::sdl2_event_helper::replace_event_handler(mk::sdl2_event_helper::event_handler new_handler)
-> event_handler {
    this->impl->current_event_handler.swap(new_handler);
    return new_handler;
}

auto mk::sdl2_event_helper::replace_quit_handler(mk::sdl2_event_helper::event_handler new_handler)
-> event_handler {
    this->impl->current_quit_handler.swap(new_handler);
    return new_handler;
}

mk::sdl2_log_helper::sdl2_log_helper() = default;

mk::sdl2_log_helper::~sdl2_log_helper() = default;

void mk::sdl2_log_helper::log(const std::string &message) const {
    this->log(message.c_str());
}

void mk::sdl2_log_helper::log(const char *message) const {
    this->log_(message);
}

mk::sdl2_log_helper &mk::sdl2_log_helper::operator<<(const std::string &message) {
    this->log(message);
    return *this;
}

mk::sdl2_log_helper &mk::sdl2_log_helper::operator<<(const char *message) {
    this->log(message);
    return *this;
}

void mk::sdl2_log_helper::log_(const char *message) const {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", message);
}

void mk::sdl2_cerr::log_(const char *message) const {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", message);
}
}
