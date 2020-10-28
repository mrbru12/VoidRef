#pragma once

// #include "../Types/Array.h"
#include "../Graphics/Shaders.h"

namespace VRef
{
    namespace Draw
    {
        void triangle(Shader& shader, size_t size, float* vertices);
        // void triangle(GL::VAO& vao, Shader& shader, size_t size, float* vertices);
        void triangle(Shader& shader, 
                      size_t verticesSize, float* vertices, 
                      size_t indicesSize, unsigned int* indices);
        // void triangle(GL::VAO& vao, Shader& shader,
        //               size_t verticesSize, float* vertices,
        //               size_t indicesSize, unsigned int* indices);

        void line(Shader& shader, size_t size, float* vertices);
        // void line(Shader& shader,
        //           size_t verticesSize, float* vertices,
        //           size_t indicesSize, unsigned int* indices);

        // void rectangle(Shader& shader, size_t vertexArraySize, float* vertexArray);
    }
}
