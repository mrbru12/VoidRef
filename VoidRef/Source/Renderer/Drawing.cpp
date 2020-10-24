#include "Drawing.h"

#include <glad/glad.h>

#ifndef NULL
#define NULL 0
#endif

namespace VRef
{
    namespace Draw
    {
        void triangle(Shader& shader, size_t arraySize, float* vertexArray)
        {
            // -> Bind Shader program:
            shader.bind();

            // -> Send vertex data for the vertex buffer:
            glBufferData(GL_ARRAY_BUFFER, arraySize, vertexArray, GL_STATIC_DRAW);

            // glBufferData reference: https://www.khronos.org/opengl/wiki/GLAPI/glBufferData

            // GL_STREAM_DRAW: if the data is set only once and used by the GPU at most a few times.
            // GL_STATIC_DRAW : if the data is set only once and used many times.
            // GL_DYNAMIC_DRAW : if the data is changed a lot and used many times.

            // -> Send indices data for the element buffer:
            // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // -> Set how the data in VBO should be interpreted as a drawing:
            glDrawArrays(GL_TRIANGLES, 0, 3);

            // -> Unbind Shader program:
            shader.unbind();
        }

        void triangle(Shader& shader,
                      size_t vertexArraySize, float* vertexArray,
                      size_t indicesArraySize, unsigned int* indicesArray)
        {
            shader.bind();

            glBufferData(GL_ARRAY_BUFFER, vertexArraySize, vertexArray, GL_STATIC_DRAW);

            // -> Send indices data for the element buffer:
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesArraySize, indicesArray, GL_STATIC_DRAW);

            // -> Set how the data in EBO should be interpreted as a drawing
            glDrawElements(GL_TRIANGLES, indicesArraySize * sizeof(indicesArray[0]), GL_UNSIGNED_INT, NULL);
            
            shader.unbind();
        }

        /*
        void triangle(Shader& shader, Array<float>& vertexArray, Array<unsigned int>& indices)
        {
            shader.bind();

            glBufferData(GL_ARRAY_BUFFER, vertexArray.size, vertexArray.begin, GL_STATIC_DRAW);

            // -> Send indices data for the element buffer:
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size, indices.begin, GL_STATIC_DRAW);

            glDrawArrays(GL_TRIANGLES, 0, 3);

            shader.unbind();
        }
        */
    }
}
