#pragma once

// #include "../Types/Array.h"
#include "../Graphics/Shaders.h"

namespace VRef
{
    namespace Draw
    {
        void triangle(Shader& shader, size_t vertexArraySize, float* vertexArray);
        void triangle(Shader& shader, 
                      size_t vertexArraySize, float* vertexArray, 
                      size_t indicesArraySize, unsigned int* indicesArray);
        // void triangle(Shader& shader, Array<float>& vertexArray, Array<unsigned int>& indices);

        void rectangle(Shader& shader, size_t vertexArraySize, float* vertexArray);
    }
}
