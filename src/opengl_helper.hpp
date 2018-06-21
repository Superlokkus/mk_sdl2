#ifndef CG1_S70357_2017_OPENGL_HELPER_HPP
#define CG1_S70357_2017_OPENGL_HELPER_HPP

#include <string>
#include <map>
#include <cstdint>

namespace mk {

struct opengl_error : std::exception {
    opengl_error(std::string error) : std::exception(), what_(std::move(error)) {};

    const char *what() const noexcept override {
        return this->what_.c_str();
    }

private:
    std::string what_;
};

/*! @brief Utility class for glew and opengl
 *
 */
class opengl_helper final {
public:
    /*!
     * @brief Initializes glew and opengl if needed
     */
    opengl_helper();

    ~opengl_helper();

    enum struct shader_type {
        vertex_shader,
        fragment_shader,
        geometry_shader,
        tessellation_control_shader,
        tessellation_evaluation_shader,
        compute_shader,
    };

    static uint32_t shader_type_to_gl_enum(shader_type);

    class opengl_program {
    public:
        uint32_t program_id();

        opengl_program();

        virtual ~opengl_program();

        void attach_shaders(const std::map<shader_type, std::string> &shaders);

        void set_as_current_program();

        bool is_linked();

        bool is_current();

    private:
        uint32_t program_id_;

        void set_shaders(std::map<mk::opengl_helper::shader_type, std::tuple<std::string, uint32_t>> &shaders);
    };

    void praktikum01_1();

    void praktikum01_2();


};

}

#endif //CG1_S70357_2017_OPENGL_HELPER_HPP
