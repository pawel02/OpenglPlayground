#include <iostream>
#include <Engine.hpp>

int main()
{
    std::string sharedAssetsPath{ "E:/pawel/coding(learning)/c++/PlayingWithOpenGL/shared_assets/" };
    std::string basePath{ "E:/pawel/coding(learning)/c++/PlayingWithOpenGL/Example3/shaders/" };

    Engine::Window window{800, 600, "Example3"};
    if (window.createWindow())
    {
        std::cout << "Could not create the window\n";
        return -1;
    }
    window.hideCursor();


    Engine::CameraPer camera{800, 600};

    //load the example model
    Engine::Model model{sharedAssetsPath + "backpack/backpack.obj"};
    Engine::Shader model_program{ basePath + "basic.vs", basePath + "basic.gs", basePath + "basic.fs" };

    float prevTime = (float)glfwGetTime();
    float deltaTime = 0.0f;
    while (window.isOpen())
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        deltaTime = (float)glfwGetTime() - prevTime;
        prevTime = (float)glfwGetTime();
        camera.onUpdate(deltaTime);

        //draw everything that you want
        model.Draw(model_program);


        glfwSwapBuffers(window.getWindowPointer());
        glfwPollEvents();
    }


    return 0;
}