#include "shader.h"

#include <GL/glew.h>

std::string readFile(const char* filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();

    // std::cout << content << std::endl;

    return content;
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    try {
        this->vertexShaderSource = readFile(vertexShaderPath);
        this->fragmentShaderSource = readFile(fragmentShaderPath);
    } catch (...) {
        std::cerr << "Error: Opening shaders" << std::endl;
        exit(-1);
    }

    const char* vertexShaderCode = vertexShaderSource.c_str();
    const char* fragmentShaderCode = fragmentShaderSource.c_str();

    // Compile shaders
    GLuint vertexShader, fragmentShader;
    int success;
    char infoLog[512];

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error: Failed to compile vertex shader\n"
                  << infoLog << std::endl;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Error: Failed to compile fragment shader\n"
                  << infoLog << std::endl;
    }

    // Create shader program and link shaders
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "Error: Failed to link shaders\n"
                  << infoLog << std::endl;
    }

    // Delete shaders as they're no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Use shader program
void Shader::use() {
    glUseProgram(ID);
}

// Set a uniform integer value
void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

// Set a uniform float value
void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

// Set a uniform 4x4 matrix value
void Shader::setMat4(const std::string& name, const float* value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value);
}

// Set a uniform 2-component vector value
void Shader::setVec2(const std::string& name, float x, float y) const {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

// Set a uniform 3-component vector value
void Shader::setVec3(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

// Set a uniform integer value
void Shader::setUniform(const std::string& name, int value) const {
    this->setInt(name.c_str(), value);
}

// Set a uniform float value
void Shader::setUniform(const std::string& name, float value) const {
    this->setFloat(name.c_str(), value);
}

// Set a uniform 4x4 matrix value
void Shader::setUniform(const std::string& name, const float* value) const {
    this->setMat4(name.c_str(), value);
}

// Set a uniform 3-component vector value
void Shader::setUniform(const std::string& name, float x, float y) const {
    this->setVec2(name.c_str(), x, y);
}

// Set a uniform 3-component vector value
void Shader::setUniform(const std::string& name, float x, float y, float z) const {
    this->setVec3(name.c_str(), x, y, z);
}

void Shader::setUniform(const std::string& name, Matrix4f value) const {
    this->setMat4(name.c_str(), value.getAll());
}

void Shader::setUniform(const std::string& name, Vector3f value) const {
    this->setVec3(name.c_str(), value.x, value.y, value.z);
}

void Shader::setUniform(const std::string& name, Vector2f value) const {
    this->setVec2(name.c_str(), value.x, value.y);
}