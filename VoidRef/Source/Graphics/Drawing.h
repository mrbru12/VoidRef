#pragma once

#include <glad/glad.h>

#include "../Graphics/Shaders.h"

namespace VRef
{
    namespace Draw
    {
        void triangle(Shader& shader, size_t size, float* vertices, GLenum usage = GL_STATIC_DRAW);
        void triangle(Shader& shader, 
                      size_t verticesSize, float* vertices, 
                      size_t indicesSize, unsigned int* indices,
                      GLenum usage = GL_STATIC_DRAW);

        void line(Shader& shader, size_t size, float* vertices, GLenum usage = GL_STATIC_DRAW);
        void line(Shader& shader,
                  size_t verticesSize, float* vertices,
                  size_t indicesSize, unsigned int* indices,
                  GLenum usage = GL_STATIC_DRAW);

        // void rectangle(Shader& shader, size_t vertexArraySize, float* vertexArray, GLenum usage = GL_STATIC_DRAW);

        // * Pra desenhar o polygon usar GL_LINE_LOOP no glDrawArrays!
        // void polygon(Shader& shader, size_t size, float* vertices, GLenum usage = GL_STATIC_DRAW);
    }
}
