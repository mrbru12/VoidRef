// -> Headers being implemented here:
#include "Program.h"

// -> Not my own headers:
#include <glad/glad.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <stdio.h>

// -> My own headers:
#include "../Debug/SysLog.h"

/*
void printRenderDrivers()
{
    SDL_RendererInfo info;

    printf("[Render Drivers]: ");

    for (int i = 0; i < SDL_GetNumRenderDrivers(); i++)
    {
        SDL_GetRenderDriverInfo(i, &info);

        printf("%s ", info.name);
    }

    printf("\n");
}
*/

bool initOpenGL(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
    // -> Vertex array object assign:
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // -> Vertex buffer object assign:
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // -> Element buffer object assign:
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // -> Vertex attributes configuration:
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return true;
}

namespace VRef
{
    bool Program::create(const char* title, int width, int height)
    {
        // -> SDL Subsystems initialization:
        // * Check https://wiki.libsdl.org/SDL_Init for hints!
        if (!Debug::log(VREF_INFO, "Initialized SDL Subsystems!", !System::logOnSdlError(SDL_Init(SDL_INIT_VIDEO))))
            return false;
        //  SDL_Quit();

        // -> SDL Image initialization:
        if (!Debug::log(VREF_INFO, "Initialized SDL Image!", !System::logOnSdlError(!IMG_Init(IMG_INIT_PNG))))
            return false;
        //  SDL_Quit();
        
        // -> OpenGL attributes declaration:
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        // SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // -> SDL Window initialization:
        // * Check https://wiki.libsdl.org/SDL_CreateWindow for flag hints!
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL); // SDL_WINDOW_SHOWN
        if (!Debug::log(VREF_INFO, "Initialized SDL Window!", !System::logOnSdlError(window == NULL))) // (!window)
            return false;
        //  SDL_DestroyWindow(window);
        //  SDL_Quit();

        // -> Creating OpenGL context in SDL window:
        context = SDL_GL_CreateContext(window);
        System::logOnSdlError(context == NULL);

        // -> Glad initialization:
        Debug::log(VREF_ERROR, "Failed to initialize Glad!", !gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress));

        // -> Use VSync to set fixed screen update:
        System::logOnSdlError(SDL_GL_SetSwapInterval(1));

        // -> OpenGL initialization:
        if (System::logGlError("Failed to initialize OpenGL!", !initOpenGL(VAO, VBO, EBO)))
            return false;
        //  SDL_DestroyWindow(window);
        //  SDL_Quit();

        // -> Set OpenGL renderer viewport to suit window size:
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        glViewport(0, 0, w, h);

        // -> Set window clear color:
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // -> SDL Renderer initialization:
        /*
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!Debug::log(VREF_INFO, "Initialized SDL Renderer!", !System::logOnSdlError(renderer == NULL))) // (!renderer)
            return false;
        */
        //  SDL_DestroyRenderer(renderer);
        //  SDL_DestroyWindow(window);
        //  SDL_Quit();
        // printRenderDrivers(); // Show available render drivers!

        // -> User onCreate:
        if (!onCreate())
            return false;

        return true;
    }
}
