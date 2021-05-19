#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

// this debugging infor should only be displayed in DEBUG mode
#ifdef _DEBUG
#define glCheckError(x) x;\
    Engine::Debugging::glCheckError_(__FILE__, __LINE__);
#else
#define glCheckError(x) x;
#endif

namespace Engine
{
    namespace Debugging
    {
        void APIENTRY glDebugOutput(GLenum source,
            GLenum type,
            unsigned int id,
            GLenum severity,
            GLsizei length,
            const char* message,
            const void* userParam);
        void initializeDebugger();
        void glCheckError_(const char* file, int line);
    }
}