#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "../Shaders/Shader.hpp"
#include "../Events/MouseEvents.hpp"
#include "../Events/KeyboardEvents.hpp"

#include "../Core/Buffers.hpp"

namespace Engine
{

struct cameraMatricies
{
	glm::mat4 projection;
	glm::mat4 view;
};

/*
Perspective camera wrapper
This will share its view and projection matricies with all the shaders through
Uniform buffer in binding position 1 and std140 layout

Default camera controls are
WASD 
and mouse moving
*/
class CameraPer
{
public:
	CameraPer(float screenWidth, float screenHeight) noexcept;
	~CameraPer() = default;

	void onUpdate(float deltaTime);

	const cameraMatricies getMatricies() const noexcept { return{ _projection, _view}; }

private:
	bool handleKeyPressed(Events::KeyPressedEvent* ev);
	bool handleKeyReleased(Events::KeyReleasedEvent* ev);

	bool handleMouse(double deltaTime);

    //updates all of the values for the shaders using the UBO
    void updateUBO();
private:
    //UBO for sharing the view projection matrix with all the shaders
    UniformBuffer _UBO;

	glm::mat4 _projection;
	glm::mat4 _view = glm::mat4{1.0f};

    //initially spawn slightly in the back
	glm::vec3 _cameraPos = { 0.0f, 0.0f, 3.0f };
	glm::vec3 _cameraFront = { 0.0f, 0.0f, -1.0f };
	glm::vec3 _cameraUp = { 0.0f, 1.0f, 0.0f };
	

	float _cameraSpeed = 5.0f;

	char _keysDown = 0x00;

	//mouse movement
	char _mouseState = 0x00; // BIT(0) first movement, BIT(1) move_moved

	glm::vec2 _mouseMoved;

	double _lastX = 0.0;
	double _lastY = 0.0;

	float _sensitivity = 0.1f;

	float _yaw = -90.0f;
	float _pitch = 0.0f;
};

}