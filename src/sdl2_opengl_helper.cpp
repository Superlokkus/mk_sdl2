#include "sdl2_opengl_helper.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_events.h>
#include <cstdlib>

mk::sdl2_error::sdl2_error(const std::string &what) :
        runtime_error(what + " SDL:" + SDL_GetError()) {
    SDL_ClearError();

}

mk::sdl2_error::sdl2_error(const char *what) :
        runtime_error(std::string(what) + " SDL:" + SDL_GetError()) {
    SDL_ClearError();
}

struct mk::sdl2_opengl_helper::impl {
    SDL_Window *mainwindow{nullptr};
    SDL_GLContext maincontext{};
    const Uint32 sdl_init_flags = SDL_INIT_VIDEO;
};

void mk::sdl2_opengl_helper::redraw(void) {
    SDL_GL_SwapWindow(this->impl->mainwindow);
}

mk::sdl2_opengl_helper::sdl2_opengl_helper(int gl_major, int gl_minor) :
        impl(new struct impl()) {
    if (!SDL_WasInit(this->impl->sdl_init_flags)) {
        if (SDL_Init(this->impl->sdl_init_flags) != 0)
            throw sdl2_error("Unable to initialize SDL");
        if (SDL_InitSubSystem(this->impl->sdl_init_flags) != 0)
            throw sdl2_error("Unable to initialize sub system of SDL");
    }

    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gl_major))
        throw sdl2_error("Unable to set gl major version to " + std::to_string(gl_major));
    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gl_minor))
        throw sdl2_error("Unable to set gl minor version to " + std::to_string(gl_minor));
    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE))
        throw sdl2_error("Unable to set gl profile");

    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    /* Create our window centered at 512x512 resolution */
    this->impl->mainwindow = SDL_CreateWindow("s70357", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                              800, 600,
                                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    if (!this->impl->mainwindow) {
        SDL_QuitSubSystem(this->impl->sdl_init_flags);
        throw sdl2_error("Unable to create window");
    }

    this->impl->maincontext = SDL_GL_CreateContext(this->impl->mainwindow);
    if (!this->impl->maincontext) {
        SDL_DestroyWindow(this->impl->mainwindow);
        SDL_QuitSubSystem(this->impl->sdl_init_flags);
        throw sdl2_error("Unable to create context");
    }
}

mk::sdl2_opengl_helper::~sdl2_opengl_helper() {
    SDL_GL_DeleteContext(this->impl->maincontext);
    SDL_DestroyWindow(this->impl->mainwindow);
    SDL_QuitSubSystem(this->impl->sdl_init_flags);
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
