#include "opengl_helper.hpp"

#include <GL/glew.h>
#include "LoadShader.hpp"


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
    program = loadShaders(vertexShader, fragmentShader, "", "", "", "");
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



