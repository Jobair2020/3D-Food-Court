#ifndef parabola_h
#define parabola_h

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"

class Paraboloid {
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    // Constructor
    float scaleX, scaleY, scaleZ;

    Paraboloid(float a = 1.0f, float b = 1.0f, float c = 1.0f, int uSegments = 50, int vSegments = 50,
        float scaleX = 1.0f, float scaleY = 1.0f, float scaleZ = 1.0f)
        : a(a), b(b), c(c), uSegments(uSegments), vSegments(vSegments),
        scaleX(scaleX), scaleY(scaleY), scaleZ(scaleZ),
        ambient(glm::vec3(0.8f, 0.8f, 0.8f)),   // Light gray ambient for a soft transparent effect
        diffuse(glm::vec3(1.0f, 1.0f, 1.0f)),   // Bright white diffuse for strong light
        specular(glm::vec3(1.0f, 1.0f, 1.0f)),   // Pure white specular for maximum highlight
        shininess(64.0f)
    {
        generateVertices();
        generateIndices();
        setupBuffers();
    }

    // Destructor
    ~Paraboloid() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void drawParaboloid(Shader& shader, glm::mat4 model) const {
        shader.use();
        shader.setVec3("material.ambient", ambient);
        shader.setVec3("material.diffuse", diffuse);
        shader.setVec3("material.specular", specular);
        shader.setFloat("material.shininess", shininess);

        model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ)); // Additional scaling
        shader.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

private:
    float a, b, c;
    int uSegments, vSegments;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO;

    void generateVertices() {
        for (int i = 0; i <= vSegments; ++i) {
            float v = i * (1.0f / vSegments);  // Normalized height parameter [0, 1]
            for (int j = 0; j <= uSegments; ++j) {
                float u = j * (2.0f * glm::pi<float>() / uSegments);

                // Parametric equations for a paraboloid facing the Y direction

                float x = scaleX * a * v * cos(u);
                float z = scaleZ * b * v * sin(u);
                float y = scaleY * c * v * v;

                // Normals calculation for a paraboloid
                glm::vec3 normal = glm::normalize(glm::vec3(
                    2 * x / (a * a),
                    -1.0f / (c * c),
                    2 * z / (b * b)
                ));

                // Add to vertex list
                vertices.push_back(x);
                vertices.push_back(y);  // Y now aligns with the height axis
                vertices.push_back(z);
                vertices.push_back(normal.x);
                vertices.push_back(normal.y);
                vertices.push_back(normal.z);
            }
        }
    }


    void generateIndices() {
        for (int i = 0; i < vSegments; ++i) {
            for (int j = 0; j < uSegments; ++j) {
                int p1 = i * (uSegments + 1) + j;
                int p2 = p1 + uSegments + 1;

                indices.push_back(p1);
                indices.push_back(p2);
                indices.push_back(p1 + 1);

                indices.push_back(p1 + 1);
                indices.push_back(p2);
                indices.push_back(p2 + 1);
            }
        }
    }

    void setupBuffers() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // Vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

        // Normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

        glBindVertexArray(0);
    }
};

#endif /* PARABOLOID_H */