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

private:
    std::string vertexShader;
    std::string fragmentShader;
    static constexpr unsigned NumBuffers = 1;
    static constexpr unsigned NumVAOs = 1;
    static constexpr uint32_t NumVertices = 6;
    enum Attrib_IDs {
        vPosition, vColor
    };
    uint32_t VAOs[NumVAOs];
    uint32_t Buffers[NumBuffers];
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
