#include "opengl_helper.hpp"

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include <tuple>
#include <vector>


namespace {
enum VAO_IDs {
    Triangles, NumVAOs
};
enum Buffer_IDs {
    ArrayBuffer, NumBuffers
};
enum Attrib_IDs {
    vPosition, vColor
};
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 6;
GLuint program;

GLuint loadShaders(std::map<mk::opengl_helper::shader_type, std::tuple<std::string, GLuint>> &shaders);

}

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

mk::opengl_helper::opengl_helper() {
    glewExperimental = GL_TRUE;
    if (glewInit())
        throw std::runtime_error("glewInit failed");
    std::map<shader_type, std::string> shaders{
            {shader_type::vertex_shader,   vertexShader},
            {shader_type::fragment_shader, fragmentShader},
    };
    program = this->set_shaders(shaders);
    glUseProgram(program);
    glGenBuffers(NumBuffers, Buffers);//NumBuffers = 1
    glGenVertexArrays(NumVAOs, VAOs);//NumVAOs = 1
    GLfloat vertices[NumVertices][2] = {
            {-0.90, -0.90},
            {0.85,  -0.90},
            {-0.90, 0.85},
            {0.90,  -0.85},
            {0.90,  0.90},
            {-0.85, 0.90}};
    glBindVertexArray(VAOs[Triangles]);//Triangles = 0
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]); //ArrayBuffer = 0
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);//vPosition = 0
    glEnableVertexAttribArray(vPosition);
}

mk::opengl_helper::~opengl_helper() {
    glDeleteBuffers(NumBuffers, Buffers);
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

uint32_t mk::opengl_helper::set_shaders(const std::map<mk::opengl_helper::shader_type, std::string> &shaders) {
    std::map<shader_type, std::tuple<std::string, GLuint>> transformed_shaders;
    for (const auto &shader: shaders) {
        transformed_shaders[shader.first] = std::make_tuple(shader.second, 0);
    }

    return loadShaders(transformed_shaders);
}

void mk::opengl_helper::praktikum01_1() {
    glClearColor(0, 1.0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glVertexAttrib3f(vColor, 1, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices / 2);
    glVertexAttrib3f(vColor, 0, 1, 0);
    glDrawArrays(GL_LINE_LOOP, 3, NumVertices / 2);
}

void mk::opengl_helper::praktikum01_2() {
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    std::vector<std::tuple<GLfloat, GLfloat>> htw_logo_vertices = {
            {0, 0},
            {3, 0},
            {3, 15},
            {0, 15}
    };
}

namespace {
GLuint loadShaders(std::map<mk::opengl_helper::shader_type, std::tuple<std::string, GLuint>> &shaders) {

    GLint infoLogLength;
    GLint result = GL_FALSE;

    for (auto &shader : shaders) {
        const auto &shaderCode = std::get<0>(shader.second);
        GLuint &shaderId = std::get<1>(shader.second);
        std::get<1>(shader.second) = glCreateShader(mk::opengl_helper::shader_type_to_gl_enum(shader.first));
        if (shaderCode.empty())
            continue;
        std::cout << "compiling shader: " << shaderCode << "\n";
        char const *vertexShaderPointer = shaderCode.c_str();
        const GLint vertexSourceLength = shaderCode.size();
        glShaderSource(shaderId, 1, &vertexShaderPointer, &vertexSourceLength);
        glCompileShader(shaderId);

        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            printf("shader putt\n");
        }
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0) {
            std::vector<char> vertexShaderErrorMsg(infoLogLength);
            glGetShaderInfoLog(shaderId, infoLogLength, NULL, &vertexShaderErrorMsg[0]);
            printf("%s\n", &vertexShaderErrorMsg[0]);
        }

    }

    std::cout << "linking program\n";
    GLuint programID = glCreateProgram();

    for (const auto &shader: shaders) {
        const auto &shaderCode = std::get<0>(shader.second);
        const auto &shaderId = std::get<1>(shader.second);
        if (!shaderCode.empty()) {
            glAttachShader(programID, shaderId);
        }
    }
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<GLchar> progErrorMsg(infoLogLength);
        glGetProgramInfoLog(programID, infoLogLength, NULL, progErrorMsg.data());
        std::cerr << progErrorMsg.data() << "\n";
    }

    for (const auto &shader: shaders) {
        const auto &shaderCode = std::get<0>(shader.second);
        const auto &shaderId = std::get<1>(shader.second);
        glDeleteShader(shaderId);
    }


    return programID;
}
}
