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


}
#endif //CG1_S70357_2017_SDL2_HELPER_HPP
