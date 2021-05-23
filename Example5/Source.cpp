/*
Instancing Asteroid example
*/

#include <iostream>
#include <string>
#include <Engine.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
    std::string sharedAssetsPath{ "E:/pawel/coding(learning)/c++/PlayingWithOpenGL/shared_assets/" };
    std::string basePath{ "E:/pawel/coding(learning)/c++/PlayingWithOpenGL/Example5/shaders/" };


    Engine::Window window{800, 600, "Example 5"};
    if(window.createWindow())
    {
        std::cout << "could not create the window\n";
        return -1;
    }
    window.hideCursor();

    Engine::CameraPer camera{ 800, 600 };

    //load in the planet
    Engine::Model planet{ sharedAssetsPath + "planet/planet.obj" };
    Engine::Shader planetProgram{ basePath + "planet.vs", basePath + "planet.fs" };

    glm::mat4 planetModel{ 1.0f };
    planetModel = glm::translate(planetModel, glm::vec3(0.0f, 0.0f, -20.0f));
    planetModel = glm::scale(planetModel, glm::vec3(2.0f));
    planetProgram.setUniformMat4f("model", planetModel);

    //load all of the asteroids
    Engine::Model asteroid{ sharedAssetsPath + "rock/rock.obj" };
    Engine::Shader asteroidProgram{ basePath + "basic.vs", basePath + "basic.fs" };


    //create all of the asteroid model matricies
    unsigned int amount = 100000;
    glm::mat4* modelMatrices;
    modelMatrices = new glm::mat4[amount];
    srand(glfwGetTime()); // initialize random seed	
    float radius = 50.0;
    float offset = 2.5f;
    for (unsigned int i = 0; i < amount; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = (float)i / (float)amount * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f; // keep height of field smaller compared to width of x and z
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));

        // 2. scale: scale between 0.05 and 0.25f
        float scale = (rand() % 20) / 100.0f + 0.05;
        model = glm::scale(model, glm::vec3(scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = (rand() % 360);
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

        // 4. now add to list of matrices
        modelMatrices[i] = model;
    }

    Engine::VertexBuffer<glm::mat4> VBO{ modelMatrices, sizeof(glm::mat4) * amount };
    VBO.bind();
    VBO.setData();

    //fill the layout from 3 to 6 
    for (unsigned int i = 0; i < asteroid.getMeshes().size(); i++)
    {
        asteroid.getMeshes()[i].getVAO().bind();
        std::size_t vec4Size = sizeof(glm::vec4);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
    }

    glDisable(GL_BLEND);

    float prevTime = (float)glfwGetTime();
    float deltaTime = 0.0f;
    while (window.isOpen())
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        deltaTime = (float)glfwGetTime() - prevTime;
        prevTime = (float)glfwGetTime();

        camera.onUpdate(deltaTime);

        //draw everything
        planet.Draw(planetProgram);

        //draw the asteroids
        asteroidProgram.bind();
        for (unsigned int i = 0; i < asteroid.getMeshes().size(); i++)
        {
            asteroid.getMeshes()[i].getVAO().bind();
            asteroid.getMeshes()[i].textures->bindAll();
            glDrawElementsInstanced(GL_TRIANGLES, asteroid.getMeshes()[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
        }

        glfwSwapBuffers(window.getWindowPointer());
        glfwPollEvents();
    }


    return 0;
}