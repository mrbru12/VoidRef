#pragma once

#include <glad/glad.h>

namespace VRef
{ 
    namespace GL
    {
        class VAO
        {
            // VAO reference: https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Array_Object
            // TODO: Suportar mais de 1 de cada buffer. Por exmplo: por enquanto só pode 1 ter 1 VBO, mas de
            //       acordo com as docs do OpenGL um VAO pode ter até 16 VBOs diferentes!
            
        public:
            VAO(/* TODO: Quantidade de buffers de cada tipo para criar */);

            void bind();
            void unbind();

            void genBuffers(GLenum target, GLsizei n);
            
            void writeBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage);

            void bindBuffer(GLenum target, GLuint bufferId);
            // void unbindBuffer(GLenum target);

        private:
            unsigned int VaoId;
            unsigned int* VboIds;
            unsigned int* EboIds;
        };
    }
}
