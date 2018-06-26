#include "exercises.hpp"
#include <opengl_helper.hpp>
#include <sdl2_opengl_helper.hpp>

#include <GL/glew.h>
#include <vector>
#include <array>


exercises::praktikum01_1::praktikum01_1() {
    vertexShader = "#version 330 core\n"
                   "\n"
                   "layout(location = 0) in vec4 vPosition;\n"
                   "\n"
                   "void main() {\n"
                   "\tgl_Position = vPosition;\n"
                   "}";

    fragmentShader = "#version 330 core\n"
                     "\n"
                     "out vec4 fColor;\n"
                     "\n"
                     "void main() {\n"
                     "\tif(gl_PrimitiveID == 0) {\n"
                     "\t\tfColor = vec4(0.0, 0.0, 1.0, 1.0);\n"
                     "\t} else {\n"
                     "\t\tfColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
                     "\t}\n"
                     "}";


    glGenBuffers(NumBuffers, Buffers);//NumBuffers = 1
    glGenVertexArrays(NumVAOs, VAOs);//NumVAOs = 1
    GLfloat vertices[NumVertices][2] = {
            {-0.90, -0.90},
            {0.85,  -0.90},
            {-0.90, 0.85},
            {0.90,  -0.85},
            {0.90,  0.90},
            {-0.85, 0.90}};
    glBindVertexArray(VAOs[0]);//Triangles = 0
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]); //ArrayBuffer = 0
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);//vPosition = 0
    glEnableVertexAttribArray(vPosition);
}

exercises::praktikum01_1::~praktikum01_1() {
    glDeleteBuffers(NumBuffers, Buffers);
}

void exercises::praktikum01_1::draw() {
    glClearColor(0, 1.0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glVertexAttrib3f(vColor, 1, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices / 2);
    glVertexAttrib3f(vColor, 0, 1, 0);
    glDrawArrays(GL_LINE_LOOP, 3, NumVertices / 2);
}

struct exercises::praktikum01_2::impl {
    using vertex_t = std::tuple<GLfloat, GLfloat>;
    std::vector<vertex_t> htw_logo_vertices;
    std::array<GLuint, 1> buffer_objects;
    std::array<GLuint, 1> vertex_array_objects;
};

exercises::praktikum01_2::praktikum01_2() : pimpl(new struct impl) {
    this->pimpl->htw_logo_vertices = {
            {-0.90, -0.90},
            {0.85,  -0.90},
            {-0.90, 0.85},
            {0.90,  -0.85},
            {0.90,  0.90},
            {-0.85, 0.90}};
    /*{
    {0, 0},
    {3, 0},
    {3, 15},
    {0, 15},
    {0,0},
};*/
    glGenBuffers(this->pimpl->buffer_objects.max_size(), this->pimpl->buffer_objects.data());
    glGenBuffers(this->pimpl->vertex_array_objects.max_size(), this->pimpl->vertex_array_objects.data());

    //glBindVertexArray(this->pimpl->vertex_array_objects.at(0));
    glBindBuffer(GL_ARRAY_BUFFER, this->pimpl->buffer_objects.at(0));
    glBufferData(GL_ARRAY_BUFFER,
                 this->pimpl->htw_logo_vertices.size() * sizeof(decltype(this->pimpl->htw_logo_vertices)::value_type),
                 this->pimpl->htw_logo_vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);
}

exercises::praktikum01_2::~praktikum01_2() {
    glDeleteBuffers(this->pimpl->buffer_objects.size(), this->pimpl->buffer_objects.data());
    glDeleteVertexArrays(this->pimpl->vertex_array_objects.size(), this->pimpl->vertex_array_objects.data());
}

void exercises::praktikum01_2::draw() {
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(this->pimpl->vertex_array_objects.at(0));
    glVertexAttrib3f(1, 1, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, this->pimpl->htw_logo_vertices.size());
}
