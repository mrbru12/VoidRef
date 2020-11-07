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

            void setVertexAttributes(GLint size, GLenum type, GLsizei stride);
            
            // void writeBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
            // void writeBufferData(GLenum target, GLuint bufferId, GLsizeiptr size, const void* data, GLenum usage); // GLuint bufferId = 0

            void bindBuffer(GLenum target, GLuint bufferId);
            // void unbindBuffer(GLenum target);

        private:
            unsigned int vaoId;
            unsigned int* vboIds;
            unsigned int* eboIds;

            // TODO: Talvez criar um sistema de layers nos buffers usando o std::map, desse modo 
            //       eu posso fazer, por exemplo, um mapeamento dos VBOs, ou, talvez melhor, dos VAOs: 
            //       
            //       std::map<const char*, unsigned int> layers;
            //       // ou
            //       std::map<const char*, VRef::GL::VAO> layers;
            //
            //       layers["Fundo"] = VboIds[0]; // = fundoVAO;
            //       layers["Player"] = VboIds[1]; // = playerVAO; 
            //       layers["Inimigos"] = VboIds[2]; // = inimigosVAO;
        };
    }
}
