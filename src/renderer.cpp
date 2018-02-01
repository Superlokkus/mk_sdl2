#include "renderer.hpp"

#include <GL/glew.h>
#include "LoadShader.hpp"

namespace {
GLint height = 100, width = 100;
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

mk::renderer::renderer() {
    glewExperimental = GL_TRUE;
    if (glewInit())
        throw std::runtime_error("glewInit failed");
    program = loadShaders("Dreiecke.vs", "Dreiecke.fs", "", "", "", "");
    glUseProgram(program);
    glGenBuffers(NumBuffers, Buffers);
    glGenVertexArrays(NumVAOs, VAOs);
    GLfloat vertices[NumVertices][2] = {
            {-0.90, -0.90},
            {0.85,  -0.90},
            {-0.90, 0.85},
            {0.90,  -0.85},
            {0.90,  0.90},
            {-0.85, 0.90}};
    glBindVertexArray(VAOs[Triangles]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(vPosition);
}

void mk::renderer::praktikum01() {
    glClearColor(0, 1.0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAOs[Triangles]);
    glVertexAttrib3f(vColor, 1, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices / 2);
    glVertexAttrib3f(vColor, 0, 1, 0);
    glDrawArrays(GL_LINE_LOOP, 3, NumVertices / 2);
    glFlush();
}

