/*! @file sdl2_opengl_helper.hpp
 *
 * All definitions for using opengl in conjunction with sdl2, without any included sdl2 or opengl dependencies
 */
#ifndef CG1_S70357_2017_SDL2_HELPER_HPP
#define CG1_S70357_2017_SDL2_HELPER_HPP

#include <memory>
#include <exception>
#include <string>
#include <functional>
#include <iostream>

namespace mk {

struct sdl2_error : std::runtime_error {
    sdl2_error(const std::string &what);

    sdl2_error(const char *what);
};

/*! @brief Class for setting up opengl via sdl2.
 *
 */
class sdl2_opengl_helper final {
public:
    /*! @brief Sets up the opengl context, windows etc.
     *
     * @param gl_major Requested opengl major version number
     * @param gl_minor Requested opengl minor version number
     */
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

/*! @brief Class for setting up and using the sdl2 event system
 *
 */
class sdl2_event_helper final {
public:
    explicit sdl2_event_helper();

    ~sdl2_event_helper();

    /*! @brief Takes the next UI event and calls the according handler in the same thread
     * @throws Nothing except for exceptions thrown by the event handlers
     * */
    void update_ui();

    using event_handler = std::function<void(void)>;

    /*! @brief Replaces the event_handler who will get called by all events except the quit event @see replace_quit_handler
     * @param new_handler New handler to use for all events except quit
     * @return Previous installed event handler
     */
    event_handler replace_event_handler(event_handler new_handler);

    /*! @brief Set up for handling quitting of the application
     * @param new_handler New handler to use for the quit event
     * @return Previous installed quit handler
     */
    event_handler replace_quit_handler(event_handler new_handler);

private:
    struct impl;
    std::unique_ptr<impl> impl;
};

class sdl2_log_helper {
public:
    explicit sdl2_log_helper();

    virtual ~sdl2_log_helper();

    void log(const std::string &) const;

    void log(const char *) const;

    sdl2_log_helper &operator<<(const std::string &);

    sdl2_log_helper &operator<<(const char *);

protected:
    virtual void log_(const char *) const;
};

struct sdl2_cerr : sdl2_log_helper {
protected:
    void log_(const char *) const override;
};

struct sdl2_cout : sdl2_log_helper {
};

}


#endif //CG1_S70357_2017_SDL2_HELPER_HPP
