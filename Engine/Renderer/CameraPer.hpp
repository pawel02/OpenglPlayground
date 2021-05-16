#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "Camera.hpp"

#include "../Shaders/Shader.hpp"
#include "../Events/MouseEvents.hpp"
#include "../Events/KeyboardEvents.hpp"

#include "../Core/Buffers.hpp"

namespace Engine
{


/*
Perspective camera wrapper
This will share its view and projection matricies with all the shaders through
Uniform buffer in binding position 1 and std140 layout

Default camera controls are
WASD 
and mouse moving
*/
class CameraPer : public Camera
{
public:
	CameraPer(float screenWidth, float screenHeight) noexcept;
	~CameraPer() = default;

	void onUpdate(float deltaTime);

private:
	bool handleKeyPressed(Events::KeyPressedEvent* ev);
	bool handleKeyReleased(Events::KeyReleasedEvent* ev);

	bool handleMouse(double deltaTime);

    //updates all of the values for the shaders using the UBO
    void updateUBO();
private:
    //UBO for sharing the view projection matrix with all the shaders
    UniformBuffer _UBO;

    //initially spawn slightly in the back
	glm::vec3 _cameraPos = { 0.0f, 0.0f, 3.0f };
	glm::vec3 _cameraFront = { 0.0f, 0.0f, -1.0f };
	glm::vec3 _cameraUp = { 0.0f, 1.0f, 0.0f };
	

	float _cameraSpeed = 5.0f;

	char _keysDown = 0x00;

	//mouse movement
	char _mouseState = 0x00; // BIT(0) first movement, BIT(1) move_moved

	glm::vec2 _mouseMoved;

	float _lastX = 0.0f;
	float _lastY = 0.0f;

	float _sensitivity = 0.1f;

	float _yaw = -90.0f;
	float _pitch = 0.0f;
};

}