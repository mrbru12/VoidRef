#include "Drawing.h"

#include <glad/glad.h>

#ifndef NULL
#define NULL 0
#endif

void drawShape(GLenum mode, GLint first, GLsizei count,
               size_t& size, float*& vertices, 
               GLenum& usage)
{
    // -> Bind Shader program:
    // shader.bind();

    // -> Send vertex data for the vertex buffer:
    glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);

    // glBufferData reference: https://www.khronos.org/opengl/wiki/GLAPI/glBufferData

    // * Usage:
    // GL_STREAM_DRAW: if the data is set only once and used by the GPU at most a few times.
    // GL_STATIC_DRAW : if the data is set only once and used many times.
    // GL_DYNAMIC_DRAW : if the data is changed a lot and used many times.

    // -> Set how the data in VBO should be interpreted as a shape:
    glDrawArrays(mode, first, count);

    // -> Unbind Shader program:
    // shader.unbind();
}

void drawShape(GLenum mode,
               size_t& verticesSize, float*& vertices,
               size_t& indicesSize, unsigned int*& indices,
               GLenum& usage)
{
    // -> Bind Shader program:
    // shader.bind();

    // -> Send vertex data for the vertex buffer:
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, usage);

    // -> Send indices data for the element buffer:
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, usage);

    // -> Set how the data in EBO should be interpreted as a shape:
    glDrawElements(mode, indicesSize, GL_UNSIGNED_INT, NULL);
    
    // -> Unbind Shader program:
    // shader.unbind();
}

namespace VRef
{
    namespace Draw
    {
        void triangle(Shader& shader, size_t size, float* vertices, GLenum usage)
        {
            // -> Bind Shader program:
            shader.bind();

            drawShape(GL_TRIANGLES, 0, 3,
                      size, vertices, 
                      usage);

            // -> Unbind Shader program:
            shader.unbind();
        }

        void triangle(Shader& shader,
                      size_t verticesSize, float* vertices,
                      size_t indicesSize, unsigned int* indices,
                      GLenum usage)
        {
            shader.bind();

            drawShape(GL_TRIANGLES,
                      verticesSize, vertices,
                      indicesSize, indices,
                      usage);
            
            shader.unbind();
        }

        /*
        void triangle(Shader& shader, Array<float>& vertices, Array<unsigned int>& indices)
        {
            shader.bind();

            glBufferData(GL_ARRAY_BUFFER, vertices.size, vertices.begin, GL_STATIC_DRAW);

            // -> Send indices data for the element buffer:
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size, indices.begin, GL_STATIC_DRAW);

            glDrawArrays(GL_TRIANGLES, 0, 3);

            shader.unbind();
        }
        */

        void line(Shader& shader, size_t size, float* vertices, GLenum usage)
        {
            shader.bind();

            drawShape(GL_LINES, 0, 2,
                      size, vertices,
                      usage);

            shader.unbind();
        }

        void line(Shader& shader,
                  size_t verticesSize, float* vertices,
                  size_t indicesSize, unsigned int* indices,
                  GLenum usage)
        {
            shader.bind();

            drawShape(GL_LINES,
                      verticesSize, vertices,
                      indicesSize, indices,
                      usage);

            shader.unbind();
        }

        /*
        void rectangle(Shader& shader, size_t size, float* vertices)
        {
            unsigned int indices[6] =
            {
                0, 1, 2,
                1, 2, 3
            };
            
            triangle(shader, size, vertices, sizeof(indices), indices);
        }
        */

        /*
        void polygon(Shader& shader, size_t size, float* vertices, GLenum usage)
        {
            shader.bind();

            drawShape(GL_LINE_LOOP, 0, size / sizeof(vertices[0]),
                      size, vertices,
                      usage);

            shader.unbind();
        }
        */
    }
}
