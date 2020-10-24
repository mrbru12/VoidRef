#include "SysLog.h"
#include "Log.h"

#include <SDL.h>
#include <stdio.h>

namespace VRef
{
    namespace System
    {
        // Function for logging OpenGL errors:
        void logGlError(const char* msg)
        {
            Debug::log("GL Error", msg);
        }

        bool logGlError(const char* msg, bool condition)
        {
            if (condition)
                logGlError(msg);

            return condition;
        }

        // Function for logging SDL errors:
        bool logOnSdlError(int errorCode)
        {
            if (errorCode != 0)
            {
                Debug::log("SDL Error", SDL_GetError());

                return true;
            }

            return false;
        }
    }

    namespace Debug
    {
        void log(const char* msg)
        {
            log(VREF_INFO, msg);
        }

        void log(const char* title, const char* msg)
        {
            printf("[%s]: %s\n", title, msg);
        }

        bool log(const char* title, const char* msg, bool condition)
        {
            if (condition)
                log(title, msg);

            return condition;
        }
    }
}
