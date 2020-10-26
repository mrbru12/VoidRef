#pragma once

namespace VRef
{
    // namespace GL

    class Shader
    {
    public:
        Shader();
        
        void loadFromMemory(const char* vertexShader, const char* fragmentShader);
        void loadFromFile(const char* vertexPath, const char* fragmentPath);

        void bind();
        void unbind();

    private:
        unsigned int programId;
        unsigned int vertexId;
        unsigned int fragmentId;
    };
}
