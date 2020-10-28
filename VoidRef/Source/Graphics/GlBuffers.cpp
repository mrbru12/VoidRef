#include "GlBuffers.h"

#include "../Debug/Log.h"

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
            glGenVertexArrays(1, &vaoId);
            bind(); // Fazer isso para automaticamente dar bind() quando criar um VAO!
            
            // -> Vertex buffer object assign:
            genBuffers(GL_ARRAY_BUFFER, 1); // glGenBuffers(1  /* vboCount */, VboIds);
            // TODO: Pensar em como eu vou fazer os binds quando tiver mais de um buffer de cada tipo!
            bindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
            
            // -> Element buffer object assign:
            genBuffers(GL_ELEMENT_ARRAY_BUFFER, 1); // glGenBuffers(1 /* eboCount */, EboIds);
            // TODO: Pensar em como eu vou fazer os binds quando tiver mais de um buffer de cada tipo!
            bindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboIds[0]);

            // -> Vertex attributes configuration:
            setVertexAttributes(3, GL_FLOAT, 3 * sizeof(float));
        }

        void VAO::bind()
        {
            glBindVertexArray(vaoId);
        }

        void VAO::unbind()
        {
            glBindVertexArray(NULL);
        }

        void VAO::genBuffers(GLenum target, GLsizei n)
        {
            switch (target)
            {
            case GL_ARRAY_BUFFER:
                glGenBuffers(n, vboIds);
                break;

            case GL_ELEMENT_ARRAY_BUFFER:
                glGenBuffers(n, eboIds);
                break;

            default:
                Debug::log(VREF_ERROR, "VAO::genBuffers(): Wrong buffer target!");
                break;
            }
        }

        void VAO::setVertexAttributes(GLint size, GLenum type, GLsizei stride)
        {
            glVertexAttribPointer(0, size, type, GL_FALSE, stride, (void*)NULL);
            glEnableVertexAttribArray(0);
        }

        // TODO: Talvez abandonar essa função e usar só a overloaded botando o parametro bufferId = 0
        void VAO::writeBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
        {
            glBufferData(target, size, data, usage);
        }

        void VAO::writeBufferData(GLenum target, GLuint bufferId, GLsizeiptr size, const void* data, GLenum usage)
        {
            bindBuffer(target, bufferId);

            writeBufferData(target, size, data, usage); // glBufferData(target, size, data, usage);
        }

        void VAO::bindBuffer(GLenum target, GLuint bufferId)
        {
            glBindBuffer(target, bufferId);
        }
    }
}
