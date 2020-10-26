#include "GlBuffers.h"

#ifndef NULL
#define NULL 0
#endif

namespace VRef
{
    namespace GL
    {
        VAO::VAO(/* GLsizei vboCount, GLsizei eboCount */)
        {
            // -> Vertex array object assign:
            glGenVertexArrays(1, &VaoId);
            // bind(); Fazer isso para automaticamente dar bind() quando criar um VAO!
            
            // -> Vertex buffer object assign:
            glGenBuffers(1  /* vboCount */, VboIds);
            // TODO: Pensar em como eu vou fazer os binds quando tiver mais de um buffer de cada tipo!
            bindBuffer(GL_ARRAY_BUFFER, VboIds[0]);
            
            // -> Element buffer object assign:
            glGenBuffers(1 /* eboCount */, EboIds);
            // TODO: Pensar em como eu vou fazer os binds quando tiver mais de um buffer de cada tipo!
            bindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboIds[0]);
        }

        void VAO::writeBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
        {

        }

        void VAO::bind()
        {
            glBindVertexArray(VaoId);
        }

        void VAO::unbind()
        {
            glBindVertexArray(NULL);
        }

        void VAO::bindBuffer(GLenum target, GLuint bufferId)
        {
            glBindBuffer(target, bufferId);
        }
    }
}
