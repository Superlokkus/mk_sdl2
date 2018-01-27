#ifndef CG1_S70357_2017_SDL2_HELPER_HPP
#define CG1_S70357_2017_SDL2_HELPER_HPP

#include <memory>
#include <exception>
#include <string>

namespace mk {

struct sdl2_error : std::runtime_error {
    sdl2_error(const std::string &what);

    sdl2_error(const char *what);
};

class sdl2_helper final {
public:
    sdl2_helper(int gl_major = 3, int gl_minor = 3);

    void redraw(void);

    ~sdl2_helper();

private:
    struct impl;
    std::unique_ptr<impl> impl;
};


}


#endif //CG1_S70357_2017_SDL2_HELPER_HPP
