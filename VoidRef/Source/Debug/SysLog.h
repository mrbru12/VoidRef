#pragma once

#include "Log.h"

namespace VRef
{
    namespace System
    {
        void logGlError(const char* msg);
        bool logGlError(const char* msg, bool condition);

        /// <summary>
        /// Check for errors in a SDL function call
        /// </summary>
        /// <param name="errorCode">== 0 means no errors</param>
        /// <returns>false if no errors</returns>
        bool logOnSdlError(int errorCode);
    }
}
