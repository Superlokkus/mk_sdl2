/*! @file mk_sdl2/sdl2_vulcan_helper.hpp
 *
 */

#ifndef TEST_SDL2_SDL2_VULCAN_HELPER_HPP
#define TEST_SDL2_SDL2_VULCAN_HELPER_HPP

#include <memory>

namespace mk {

class sdl2_vulcan_helper final {
public:
    explicit sdl2_vulcan_helper();

    void redraw(void);

    ~sdl2_vulcan_helper();

private:
    struct impl;
    std::unique_ptr<impl> pimpl;
};

}
#endif //TEST_SDL2_SDL2_VULCAN_HELPER_HPP
