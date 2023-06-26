#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::string readFile(const char* filePath);

class Shader {
   public:
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, const float* value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;

   private:
    std::string vertexShaderSource;
    std::string fragmentShaderSource;

    unsigned int ID;
};

#endif  // SHADER_H