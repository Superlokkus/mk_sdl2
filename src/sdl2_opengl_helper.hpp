/*! @file sdl2_opengl_helper.hpp
 */
#ifndef CG1_S70357_2017_SDL2_HELPER_HPP
#define CG1_S70357_2017_SDL2_HELPER_HPP

#include <memory>
#include <exception>
#include <string>
#include <functional>

namespace mk {

struct sdl2_error : std::runtime_error {
    sdl2_error(const std::string &what);

    sdl2_error(const char *what);
};

class sdl2_opengl_helper final {
public:
    explicit sdl2_opengl_helper(int gl_major = 3, int gl_minor = 3);

    /*! Swaps the double buffered window
     * @note According to SDL2 "On Mac OS X make sure you bind 0 to the draw framebuffer before swapping the window, otherwise nothing will happen. See this blog post for more info."
     */
    void redraw(void);

    ~sdl2_opengl_helper();

private:
    struct impl;
    std::unique_ptr<impl> impl;
};

class sdl2_event_helper final {
public:
    explicit sdl2_event_helper();

    ~sdl2_event_helper();

    /*! Takes the next UI event and calls the according handler*/
    void update_ui();

    using event_handler = std::function<void(void)>;

    event_handler replace_event_handler(event_handler);

    event_handler replace_quit_handler(event_handler);

private:
    struct impl;
    std::unique_ptr<impl> impl;
};


}


#endif //CG1_S70357_2017_SDL2_HELPER_HPP
