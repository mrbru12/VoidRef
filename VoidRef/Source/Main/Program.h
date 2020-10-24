#pragma once

#include <SDL.h>

namespace VRef
{
    class Program
    {
    public: // |Variables|

    public: // |Methods|
        Program();

        bool create(const char* title, int width, int height);
        void run();

    protected:
        virtual bool onCreate();
        virtual bool onUpdate();
        virtual void onDestroy();

    private: // |Variables|
        // OpenGL SDL context:
        SDL_GLContext context;

        // OpenGL manipulable objects:
        unsigned int VAO; // Vertex Array Object
        unsigned int VBO; // Vertex Buffer Object
        unsigned int EBO; // Element Buffer Object

        // SDL objects:
        SDL_Window* window;
        
    private: // |Methods|

    };
}
