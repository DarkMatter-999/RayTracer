#include "mesh.h"

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<float>& colors)
    : vertices(vertices), indices(indices), colors(colors) {
    // Generate and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

   // Generate VBO and store vertex data
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float) + colors.size() * sizeof(float), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
    glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), colors.size() * sizeof(float), colors.data());

    // Generate EBO and store index data
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);       

    // Set vertex attribute pointers for positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    // Set vertex attribute pointers for colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(vertices.size() * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Store the number of vertices for rendering
    vertexCount = indices.size(); 
}

void Mesh::render(Shader& shader) {
    // Bind VAO and shader
    glBindVertexArray(VAO);
    shader.use();

    // Render the mesh
    glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);

    // Unbind VAO
    glBindVertexArray(0);
}