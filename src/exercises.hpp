/*!
 * @file Lösungen Markus Klemm
 */
#ifndef CG1_S70357_2017_EXERCISES_HPP
#define CG1_S70357_2017_EXERCISES_HPP

#include "opengl_helper.hpp"

#include <memory>

namespace exercises {
struct praktikum01_1 {
    explicit praktikum01_1();

    ~praktikum01_1();

    std::map<mk::opengl_helper::shader_type, std::string> shaders() const {
        return std::map<mk::opengl_helper::shader_type, std::string>{
                {mk::opengl_helper::shader_type::vertex_shader,   vertexShader},
                {mk::opengl_helper::shader_type::fragment_shader, fragmentShader},
        };
    };

    void draw();

    const std::string vertexShader = {"#version 330 core\n"
                                      "\n"
                                      "layout(location = 0) in vec4 vPosition;\n"
                                      "\n"
                                      "void main() {\n"
                                      "\tgl_Position = vPosition;\n"
                                      "}"};

    const std::string fragmentShader = {"#version 330 core\n"
                                        "\n"
                                        "out vec4 fColor;\n"
                                        "\n"
                                        "void main() {\n"
                                        "\tif(gl_PrimitiveID == 0) {\n"
                                        "\t\tfColor = vec4(0.0, 0.0, 1.0, 1.0);\n"
                                        "\t} else {\n"
                                        "\t\tfColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
                                        "\t}\n"
                                        "}"};
};

struct praktikum01_2 final {

    explicit praktikum01_2();

    ~praktikum01_2();

    void draw();

private:
    struct impl;
    std::unique_ptr<impl> impl;
};

}

#endif //CG1_S70357_2017_EXERCISES_HPP
