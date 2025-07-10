//
//  cone.h
//  test
//
//  Created by [Your Name] on [Date].
//

#ifndef cone_h
#define cone_h

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

#define PI 3.1416

using namespace std;

class Cone
{
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    Cone(float radius = 1.0f, float height = 1.5f, int sectorCount = 36,
        glm::vec3 amb = glm::vec3(0.0f, 0.6f, 0.3f), glm::vec3 diff = glm::vec3(0.0f, 0.8f, 0.4f),
        glm::vec3 spec = glm::vec3(0.2f, 0.5f, 0.3f), float shiny = 32.0f) : verticesStride(24)
    {
        set(radius, height, sectorCount, amb, diff, spec, shiny);
        buildCoordinatesAndIndices();
        buildVertices();

        glGenVertexArrays(1, &coneVAO);
        glBindVertexArray(coneVAO);

        // Create VBO
        unsigned int coneVBO;
        glGenBuffers(1, &coneVBO);
        glBindBuffer(GL_ARRAY_BUFFER, coneVBO);
        glBufferData(GL_ARRAY_BUFFER, this->getVertexSize(), this->getVertices(), GL_STATIC_DRAW);

        // Create EBO
        unsigned int coneEBO;
        glGenBuffers(1, &coneEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, coneEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->getIndexSize(), this->getIndices(), GL_STATIC_DRAW);

        // Vertex attributes
        glEnableVertexAttribArray(0); // Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, verticesStride, (void*)0);
        glEnableVertexAttribArray(1); // Normal
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, verticesStride, (void*)(sizeof(float) * 3));

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    ~Cone() {}

    void set(float radius, float height, int sectors, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float shiny)
    {
        this->radius = radius > 0 ? radius : 1.0f;
        this->height = height > 0 ? height : 1.0f;
        this->sectorCount = max(sectors, 3); // At least 3 sectors for a valid cone
        this->ambient = amb;
        this->diffuse = diff;
        this->specular = spec;
        this->shininess = shiny;
    }

    void drawCone(Shader& lightingShader, glm::mat4 model) const
    {
        lightingShader.use();
        lightingShader.setVec3("material.ambient", this->ambient);
        lightingShader.setVec3("material.diffuse", this->diffuse);
        lightingShader.setVec3("material.specular", this->specular);
        lightingShader.setFloat("material.shininess", this->shininess);

        lightingShader.setMat4("model", model);

        glBindVertexArray(coneVAO);
        glDrawElements(GL_TRIANGLES, this->getIndexCount(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
    }

    const float* getVertices() const { return vertices.data(); }
    unsigned int getVertexCount() const { return (unsigned int)vertices.size() / 6; }
    unsigned int getVertexSize() const { return (unsigned int)vertices.size() * sizeof(float); }
    int getVerticesStride() const { return verticesStride; }
    const unsigned int* getIndices() const { return indices.data(); }
    unsigned int getIndexSize() const { return (unsigned int)indices.size() * sizeof(unsigned int); }
    unsigned int getIndexCount() const { return (unsigned int)indices.size(); }

private:
    void buildCoordinatesAndIndices()
    {
        float sectorStep = 2 * PI / sectorCount;
        float angle;

        // Bottom circle vertices
        for (int i = 0; i <= sectorCount; ++i)
        {
            angle = i * sectorStep;
            float x = radius * cosf(angle);
            float z = radius * sinf(angle);
            coordinates.push_back(x);     // Position
            coordinates.push_back(0.0f); // Bottom at y = 0
            coordinates.push_back(z);
            normals.push_back(0.0f); // Normal for bottom circle (upward y-axis)
            normals.push_back(-1.0f);
            normals.push_back(0.0f);
        }

        // Top vertex (cone tip)
        coordinates.push_back(0.0f);
        coordinates.push_back(height);
        coordinates.push_back(0.0f);
        normals.push_back(0.0f); // Normal for tip
        normals.push_back(1.0f);
        normals.push_back(0.0f);

        // Generate indices
        int baseCenterIndex = sectorCount; // Center point of the base
        int topIndex = sectorCount + 1;   // Tip of the cone

        for (int i = 0; i < sectorCount; ++i)
        {
            // Base triangle
            indices.push_back(i);
            indices.push_back((i + 1) % sectorCount);
            indices.push_back(baseCenterIndex);

            // Side triangle
            indices.push_back(i);
            indices.push_back((i + 1) % sectorCount);
            indices.push_back(topIndex);
        }
    }

    void buildVertices()
    {
        for (size_t i = 0; i < coordinates.size(); i += 3)
        {
            vertices.push_back(coordinates[i]);     // x
            vertices.push_back(coordinates[i + 1]); // y
            vertices.push_back(coordinates[i + 2]); // z

            vertices.push_back(normals[i]);     // nx
            vertices.push_back(normals[i + 1]); // ny
            vertices.push_back(normals[i + 2]); // nz
        }
    }

    unsigned int coneVAO;
    float radius, height;
    int sectorCount;
    vector<float> vertices;
    vector<float> coordinates;
    vector<float> normals;
    vector<unsigned int> indices;
    int verticesStride;
};

#endif /* cone_h */
#pragma once
