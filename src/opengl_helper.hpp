#ifndef CG1_S70357_2017_OPENGL_HELPER_HPP
#define CG1_S70357_2017_OPENGL_HELPER_HPP

#include <string>
#include <map>
#include <cstdint>

namespace mk {

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

    void praktikum01_1();

    void praktikum01_2();

private:
    uint32_t set_shaders(const std::map<shader_type, std::string> &shaders);

};

}

#endif //CG1_S70357_2017_OPENGL_HELPER_HPP
