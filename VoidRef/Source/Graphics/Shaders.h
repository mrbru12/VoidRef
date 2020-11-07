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

        void setInt(const char* name, int value);
        void setFloat(const char* name, float value);
        void setBool(const char* name, bool value);

    private:
        unsigned int programId;
        unsigned int vertexId;
        unsigned int fragmentId;
    };
}
