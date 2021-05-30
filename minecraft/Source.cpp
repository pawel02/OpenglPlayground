#include <iostream>
#include <Engine.hpp>
#include "terrain/terrain.hpp"

int main()
{
    std::string sharedAssetsPath{ "C:/Users/pawel/Documents/coding/OpenglPlayground/shared_assets/" };
    std::string basePath{ "C:/Users/pawel/Documents/coding/OpenglPlayground/Minecraft/shaders/" };

    Engine::Window window{800, 600, "Minecraft"};
    if(window.createWindow())
    {
        std::cout << "Could not create a window.\n";
        return -1;
    }
    window.hideCursor();

    Engine::CameraPer camera{ 800, 600 };

    //create the terrain
    Terrain terrain {10, 10, basePath};

    float prevTime = static_cast<float>(glfwGetTime());
    float deltaTime = 0.0f;
    while(window.isOpen())
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        deltaTime = static_cast<float>(glfwGetTime()) - prevTime;
        prevTime = static_cast<float>(glfwGetTime());
        camera.onUpdate(deltaTime);

        // do all the drawing
        terrain.draw();

        glfwSwapBuffers(window.getWindowPointer());
        glfwPollEvents();
    }


    return 0;
}