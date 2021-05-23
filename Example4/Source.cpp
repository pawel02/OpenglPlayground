/*
Instancing example
*/

#include <iostream>
#include <string>
#include <Engine.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
    std::string sharedAssetsPath{ "E:/pawel/coding(learning)/c++/PlayingWithOpenGL/shared_assets/" };
    std::string basePath{ "E:/pawel/coding(learning)/c++/PlayingWithOpenGL/Example4/shaders/" };


    Engine::Window window{800, 600, "Example 4"};
    if(window.createWindow())
    {
        std::cout << "could not create the window\n";
        return -1;
    }

    float quadVertices[] = {
        // positions     // colors
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,

        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
         0.05f,  0.05f,  0.0f, 1.0f, 1.0f
    };

    Engine::VertexArray<float, unsigned int> VAO{
        quadVertices, sizeof(quadVertices),
        {
            Engine::VertexAttribLayout{2, GL_FLOAT, GL_FALSE, 5 * sizeof(float)},
            Engine::VertexAttribLayout{3, GL_FLOAT, GL_FALSE, 5 * sizeof(float)}
        }
    };
    VAO.CreateVertexArray();
    Engine::Shader program{ basePath + "basic.vs", basePath + "basic.fs" };


    //create the array of offsets for the quads
    glm::vec2 translations[100];
    int index = 0;
    float offset = 0.1f;

    for (int y = -5; y < 5; y++)
    {
        for (int x = -5; x < 5; x ++)
        {
            glm::vec2 translation;
            translation.x = (float)x / 5.0f + offset;
            translation.y = (float)y / 5.0f + offset;
            translations[index++] = translation;
        }
    }

    //set all the offsets 
    for (int i = 0; i < 100; i++)
    {
        program.setUniform2f((std::string("offsets[") + std::to_string(i) + std::string("]")).c_str(), translations[i]);
    }

    while (window.isOpen())
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //draw everything
        program.bind();
        VAO.bind();
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);

        glfwSwapBuffers(window.getWindowPointer());
        glfwPollEvents();
    }


    return 0;
}