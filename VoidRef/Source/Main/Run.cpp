// -> Headers being implemented here:
#include "Program.h"

// -> Not my own headers:
#include <glad/glad.h>
#include <SDL_image.h>
#include <iostream>

// -> My own headers:
#include "../Debug/SysLog.h"

namespace VRef
{
    void Program::run()
    {
        // -> Main loop:
        SDL_Event event;
        bool eventBreak = false, clientBreak = false;
        
        while (!eventBreak && !clientBreak)
        {
            // -> Event polling:
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    eventBreak = true;
                    break;
                }
            }

            // -> Window render cleanup:
            glClear(GL_COLOR_BUFFER_BIT);
            
            // -> User onUpdate:
            clientBreak = !onUpdate();

            // -> Render and display operations:
            SDL_GL_SwapWindow(window);
        }

        // -> Variables destruction and System cleanup:
        onDestroy();

        // SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        SDL_Quit();
    }
}
