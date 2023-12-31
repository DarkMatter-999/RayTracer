#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "maths.h"

std::string readFile(const char* filePath);

class Shader {
   public:
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, const float* value) const;
    void setVec2(const std::string& name, float x, float y) const;
    void setVec3(const std::string& name, float x, float y, float z) const;

    void setUniform(const std::string& name, int value) const;
    void setUniform(const std::string& name, float value) const;
    void setUniform(const std::string& name, const float* value) const;
    void setUniform(const std::string& name, float x, float y) const;
    void setUniform(const std::string& name, float x, float y, float z) const;
    void setUniform(const std::string& name, Matrix4f value) const;
    void setUniform(const std::string& name, Vector3f value) const;
    void setUniform(const std::string& name, Vector2f value) const;

    unsigned int ID;
   private:
    std::string vertexShaderSource;
    std::string fragmentShaderSource;

};

#endif  // SHADER_H