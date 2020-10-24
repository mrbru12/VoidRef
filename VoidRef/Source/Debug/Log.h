#pragma once

#define VREF_DEBUG "Debug"

#define VREF_INFO "Info"
#define VREF_WARN "Warn"
#define VREF_ERROR "Error"

namespace VRef
{
    namespace Debug
    {
        /// <summary>
        /// Logs info {msg}
        /// </summary>
        void log(const char* msg);

        /// <summary>
        /// Logs {msg} with {title}
        /// </summary>
        void log(const char* title, const char* msg);

        /// <summary>
        /// Logs {msg} with {title} if {condition} == true
        /// </summary>
        /// <returns>{condition}</returns>
        bool log(const char* title, const char* msg, bool condition);
    }
}
