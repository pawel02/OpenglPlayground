#include <iostream>
#include <Engine.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main()
{
    std::string sharedAssetsPath{ "E:/pawel/coding(learning)/c++/PlayingWithOpenGL/shared_assets/" };
    std::string basePath{ "E:/pawel/coding(learning)/c++/PlayingWithOpenGL/Example6/shaders/" };


    Engine::Window window{800, 600, "Example 5"};
    if(window.createWindow())
    {
        std::cout << "could not create the window\n";
        return -1;
    }
    window.hideCursor();

    Engine::CameraPer camera{ 800, 600 };

    //create a plane so that I have something too look at and compare the lighting on
    Engine::VertexArray<float, unsigned int> plane{Engine::Meshes::createPlane()};
    plane.CreateVertexArray();
    Engine::Texture2D textures;
    textures.addTexture(sharedAssetsPath + "wood.jpeg");
    Engine::Shader planeProgram{ basePath + "blinnPhong.vs", basePath + "blinnPhong.fs"};
    
    glm::mat4 planeMatrix{ 1.0f };
    planeMatrix = glm::translate(planeMatrix, glm::vec3(0.0f, 19.0f, 0.0f));
    planeMatrix = glm::rotate(planeMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    planeMatrix = glm::scale(planeMatrix, glm::vec3(20.0f));

    planeProgram.setUniformMat4f("model", planeMatrix);

    //set all of the lighting
    planeProgram.setUniform3f("lightPos", -3.0f, 5.0f, 1.0f);

    glDisable(GL_CULL_FACE);

    float prevTime = (float)glfwGetTime();
    float deltaTime = 0.0f;
    while(window.isOpen())
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        deltaTime = (float)glfwGetTime() - prevTime;
        prevTime = (float)glfwGetTime();

        camera.onUpdate(deltaTime);

        //draw all the things in here
        plane.bind();
        planeProgram.bind();
        textures.bindAll();
        glDrawArrays(GL_TRIANGLES, 0, plane.getCount());

        glfwSwapBuffers(window.getWindowPointer());
        glfwPollEvents();
    }

    return 0;
}