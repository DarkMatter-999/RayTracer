#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "shader.h"

class Mesh {
   public:
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<float>& colors);
    void render(Shader& shader);
    void use(Shader& shader);

   private:
    GLuint VAO, VBO, EBO;
    unsigned int vertexCount;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> colors;
};

#endif  // MESH_H
