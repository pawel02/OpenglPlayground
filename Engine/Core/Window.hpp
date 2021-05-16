#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Events/WindowEvents.hpp"

namespace Engine
{
class Window
{
public:
    Window(int width, int height, const char* name) noexcept;
    Window(int width, int height, const char* name, GLFWmonitor* monitor) noexcept;

    ~Window() noexcept;

    /*
    Creates a window
    @returns {int} - if below 0 signifies an error
    */
    int createWindow() noexcept;

    // get the window pointer
    inline GLFWwindow* getWindowPointer() const noexcept {return _window; }

    // Close the window
    inline bool close() noexcept;
    
    // Check if the window is open
    inline bool isOpen() noexcept {return !glfwWindowShouldClose(_window); }

    //cursor controls
    inline void hideCursor() noexcept {glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);}
    inline void showCursor() noexcept {glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);}

private:
    void registerEvents() noexcept;
    bool resize(Events::WindowResizeEvent* ev);

private:
    GLFWwindow* _window;

    struct WindowData
    {
        int width = 0;
        int height = 0;
        const char* name;
        GLFWmonitor* monitor = nullptr;
    };

    WindowData _windowData;
    
};
}