#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <GL/glew.h>

GLuint loadShaders(const std::string &vertexShaderCode, const std::string &fragmentShaderCode,
                   const std::string &geometryShaderCode, const std::string &tesscontrolShaderCode,
                   const std::string &tessevaluationShaderCode, const std::string &computeShaderCode) {

    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
    GLuint tesscontrolShaderID = glCreateShader(GL_TESS_CONTROL_SHADER);
    GLuint tessevaluationShaderID = glCreateShader(GL_TESS_EVALUATION_SHADER);
    GLuint computeShaderID = glCreateShader(GL_COMPUTE_SHADER);

    int infoLogLength;

    const std::map<GLuint, const std::string &> shaders{
            {vertexShaderID,         vertexShaderCode},
            {fragmentShaderID,       fragmentShaderCode},
            {geometryShaderID,       geometryShaderCode},
            {tesscontrolShaderID,    tesscontrolShaderCode},
            {tessevaluationShaderID, tessevaluationShaderCode},
            {computeShaderID,        computeShaderCode},
    };

    GLint result = GL_FALSE;

    for (const auto &shader : shaders) {
        const auto &shaderCode = shader.second;
        const auto &shaderId = shader.first;
        if (shaderCode.empty())
            continue;
        std::cout << "compiling shader: " << shader.second << "\n";
        char const *vertexShaderPointer = shaderCode.c_str();
        const GLint vertexSourceLength = shaderCode.size();
        glShaderSource(shaderId, 1, &vertexShaderPointer, &vertexSourceLength);
        glCompileShader(shaderId);

        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            printf("shader putt\n");
        }
        glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0) {
            std::vector<char> vertexShaderErrorMsg(infoLogLength);
            glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMsg[0]);
            printf("%s\n", &vertexShaderErrorMsg[0]);
        }

    }

    std::cout << "linking program\n";
    GLuint programID = glCreateProgram();

    for (const auto &shader: shaders) {
        if (!shader.second.empty()) {
            glAttachShader(programID, shader.first);
        }
    }
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> progErrorMsg(infoLogLength);
        glGetProgramInfoLog(programID, infoLogLength, NULL, &progErrorMsg[0]);
        printf("%s\n", &progErrorMsg[0]);
    }

    for (const auto &shader: shaders) {
        glDeleteShader(shader.first);
    }


    return programID;
}
