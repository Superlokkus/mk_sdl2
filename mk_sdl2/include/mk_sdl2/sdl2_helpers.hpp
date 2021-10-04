#ifndef CG1_S70357_2017_SDL2_HELPERS_HPP
#define CG1_S70357_2017_SDL2_HELPERS_HPP

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
#endif //CG1_S70357_2017_SDL2_HELPERS_HPP
