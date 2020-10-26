#include "Shaders.h"

#include <glad/glad.h>
#include <stdio.h>
#include <cstring>

#include "../Debug/SysLog.h"

void compileShaderSource(unsigned int& shaderId, const char* shaderSource)
{
    // Setting and compiling shader's source code:
    glShaderSource(shaderId, 1, &shaderSource, NULL);
    glCompileShader(shaderId);
    
    // Checking for shader compilation errors:
    int success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shaderId, sizeof(infoLog), NULL, infoLog);
        
        VRef::System::logGlError("Bad shader compilation! *ERROR INFO BELOW*");
        VRef::Debug::log(infoLog);
    }
}

void concatenateFileLines(const char* path, const size_t& textBufferSize, char* textBuffer)
{
    FILE* file;

    // Check for errors at file path openning:
    VRef::Debug::log(VREF_ERROR, "Couldn't open file path", fopen_s(&file, path, "r"));
    
    // Check if file != NULL to please the compiler:
    if (file)
    {
        char lineBuffer[256];
        while (fgets(lineBuffer, sizeof(lineBuffer), file))
            strncat_s(textBuffer, textBufferSize, lineBuffer, textBufferSize - strlen(textBuffer));
        
        fclose(file);
    }
}

namespace VRef
{
    Shader::Shader()
        : programId(NULL), vertexId(NULL), fragmentId(NULL)
    {
    }

    void Shader::loadFromMemory(const char* vertexShader, const char* fragmentShader)
    {
        vertexId = glCreateShader(GL_VERTEX_SHADER);
        compileShaderSource(vertexId, vertexShader);

        fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
        compileShaderSource(fragmentId, fragmentShader);

        // Shader program will be used to bound the shaders:
        programId = glCreateProgram();

        glAttachShader(programId, vertexId);
        glAttachShader(programId, fragmentId);

        // Shaders compiled code linking:
        glLinkProgram(programId);

        // Checking for shader linking errors:
        int success;
        glGetProgramiv(programId, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);

            VRef::System::logGlError("Bad shader linking! *ERROR INFO BELOW*");
            VRef::Debug::log(infoLog);
        }

        // We can delete compiled shader objects after linking:
        glDeleteShader(vertexId);
        glDeleteShader(fragmentId);
    }

    void Shader::loadFromFile(const char* vertexPath, const char* fragmentPath)
    {
        const size_t size = 1024 * 10;

        char* vertexShader = new char[size] { NULL };
        concatenateFileLines(vertexPath, size, vertexShader);

        char* fragmentShader = new char[size] { NULL };
        concatenateFileLines(fragmentPath, size, fragmentShader);

        // Little debug logging for checks:
        /*
        if (debug)
        {
            Debug::log(VREF_DEBUG, "*VERTEX SHADER DEBUG BELOW*");
            printf("%s\n", vertexShader);

            Debug::log(VREF_DEBUG, "*FRAGMENT SHADER DEBUG BELOW*");
            printf("%s\n", fragmentShader);
        }
        */

        loadFromMemory(vertexShader, fragmentShader);
            
        delete[] vertexShader;
        delete[] fragmentShader;
    }

    void Shader::bind()
    {
        glUseProgram(programId);
    }

    void Shader::unbind()
    {
        glUseProgram(NULL);
    }
}
