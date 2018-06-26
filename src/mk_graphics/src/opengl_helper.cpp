#include <opengl_helper.hpp>

#include <GL/glew.h>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include <tuple>
#include <vector>

mk::opengl_helper::opengl_helper() {
    glewExperimental = GL_TRUE;
    if (glewInit())
        throw std::runtime_error("glewInit failed");
}

uint32_t mk::opengl_helper::opengl_program::program_id() {
    return this->program_id_;
}

mk::opengl_helper::opengl_program::opengl_program()
        : program_id_(0) {
    this->program_id_ = glCreateProgram();
    if (this->program_id_ == 0)
        throw opengl_error("glCreateProgram failed");
}

mk::opengl_helper::opengl_program::~opengl_program() {
    glDeleteProgram(this->program_id_);
}

void mk::opengl_helper::opengl_program::attach_shaders(
        const std::map<mk::opengl_helper::shader_type, std::string> &shaders) {

    std::map<shader_type, std::tuple<std::string, GLuint>> transformed_shaders;
    for (const auto &shader: shaders) {
        transformed_shaders[shader.first] = std::make_tuple(shader.second, 0);
    }

    this->set_shaders(transformed_shaders);
}

void mk::opengl_helper::opengl_program::set_as_current_program() {
    glUseProgram(this->program_id_);

    if (!this->is_linked())
        throw opengl_error("program not linked");
    if (!this->is_current())
        throw opengl_error("glUseProgram failed, program is not current");
}

bool mk::opengl_helper::opengl_program::is_linked() {
    GLint param = GL_TRUE;
    glGetProgramiv(this->program_id_, GL_LINK_STATUS, &param);
    return param;
}

bool mk::opengl_helper::opengl_program::is_current() {
    int64_t current_program{0};
    glGetInteger64v(GL_CURRENT_PROGRAM, &current_program);
    return current_program == this->program_id_;
}

uint32_t mk::opengl_helper::shader_type_to_gl_enum(shader_type shader_type) {
    uint32_t value{};
    switch (shader_type) {
        case shader_type::vertex_shader:
            value = GL_VERTEX_SHADER;
            break;
        case shader_type::fragment_shader:
            value = GL_FRAGMENT_SHADER;
            break;
        case shader_type::geometry_shader:
            value = GL_GEOMETRY_SHADER;
            break;
        case shader_type::tessellation_control_shader:
            value = GL_TESS_CONTROL_SHADER;
            break;
        case shader_type::tessellation_evaluation_shader:
            value = GL_TESS_EVALUATION_SHADER;
            break;
        case shader_type::compute_shader:
            value = GL_COMPUTE_SHADER;
            break;
        default:
            value = 0;
    }

    return value;
}

void mk::opengl_helper::opengl_program::set_shaders(
        std::map<mk::opengl_helper::shader_type, std::tuple<std::string, GLuint>> &shaders) {

    const auto programID = this->program_id_;

    GLint infoLogLength;

    for (auto &shader : shaders) {
        const auto &shaderCode = std::get<0>(shader.second);
        GLuint &shaderId = std::get<1>(shader.second);
        std::get<1>(shader.second) = glCreateShader(mk::opengl_helper::shader_type_to_gl_enum(shader.first));
        if (shaderCode.empty())
            continue;
        char const *vertexShaderPointer = shaderCode.c_str();
        const GLint vertexSourceLength = shaderCode.size();
        glShaderSource(shaderId, 1, &vertexShaderPointer, &vertexSourceLength);
        glCompileShader(shaderId);

        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0) {
            std::vector<char> vertexShaderErrorMsg(infoLogLength);
            glGetShaderInfoLog(shaderId, infoLogLength, NULL, &vertexShaderErrorMsg[0]);
            throw opengl_error{std::string{vertexShaderErrorMsg.data()}};
        }

    }

    for (const auto &shader: shaders) {
        const auto &shaderCode = std::get<0>(shader.second);
        const auto &shaderId = std::get<1>(shader.second);
        if (!shaderCode.empty()) {
            glAttachShader(programID, shaderId);
        }
    }

    glLinkProgram(this->program_id_);

    for (const auto &shader: shaders) {
        const auto &shaderCode = std::get<0>(shader.second);
        const auto &shaderId = std::get<1>(shader.second);
        glDeleteShader(shaderId);
    }

}

