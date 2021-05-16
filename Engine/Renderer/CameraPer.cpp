#include "../Core/Core.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CameraPer.hpp"
#include "../Events/WindowEvents.hpp"
#include <GLFW/glfw3.h>

namespace Engine
{
using namespace Events;

CameraPer::CameraPer(Shader* program, float screenWidth, float screenHeight) noexcept
	:_mouseMoved{0.0, 0.0},
	_projection{ glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f) },
    _UBO{(sizeof(glm::mat4) + sizeof(glm::vec3))}
{
    _UBO.bindBufferBlock(0);

	EventBus::subscribe<KeyPressedEvent>([&](BasicEvent* ev) {
		return handleKeyPressed(static_cast<KeyPressedEvent*>(ev));
	});
	EventBus::subscribe<KeyReleasedEvent>([&](BasicEvent* ev) {
		return handleKeyReleased(static_cast<KeyReleasedEvent*>(ev));
	});
	EventBus::subscribe<MouseMovedEvent>([&](BasicEvent* ev) {
		_mouseState |= BIT(1);
		_mouseMoved = static_cast<MouseMovedEvent*>(ev)->getPos();
		return false;
	});

	EventBus::subscribe<WindowResizeEvent>([&](BasicEvent* ev) {
		glm::vec2 size = static_cast<WindowResizeEvent*>(ev)->getSize();
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(size.x / size.y), 0.1f, 100.0f);

        updateUBO();
		return false;
	});
}

void CameraPer::onUpdate(float deltaTime)
{
	float speed = _cameraSpeed * deltaTime;
	if (_keysDown & BIT(0)) // W
	{
		_cameraPos += speed * _cameraFront;
	}
	if (_keysDown & BIT(1)) // S
	{
		_cameraPos -= speed * _cameraFront;
	}
	if (_keysDown & BIT(2)) // A
	{
        //gets the right vector and then moves in that direction
		_cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * speed;
	}
	if (_keysDown & BIT(3)) // D
	{
		_cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * speed;
	}

	//mouse movment
	if (_mouseState & BIT(1))
	{
		handleMouse(deltaTime);
		_mouseState ^= BIT(1);
	}


	_view = glm::lookAt(
		_cameraPos,
		_cameraPos + _cameraFront,
		_cameraUp
	);

    updateUBO();
}

void CameraPer::updateUBO()
{

    glm::mat4 viewProjection{_projection * _view};
    _UBO.subData(glm::value_ptr(viewProjection), 0, sizeof(glm::mat4));
    _UBO.subData(glm::value_ptr(_cameraPos), sizeof(glm::mat4), sizeof(glm::vec3));
}


bool CameraPer::handleKeyPressed(KeyPressedEvent* ev)
{

	switch (ev->getCode())
	{
		case GLFW_KEY_W:
		{
			_keysDown |= BIT(0);
			break;
		}
		case GLFW_KEY_S:
		{
			_keysDown |= BIT(1);
			break;
		}
		case GLFW_KEY_A:
		{
			_keysDown |= BIT(2);
			break;
		}
		case GLFW_KEY_D:
		{
			_keysDown |= BIT(3);
			break;
		}
	}

	return false;
}

bool CameraPer::handleKeyReleased(KeyReleasedEvent* ev)
{
	switch (ev->getCode())
	{
	case GLFW_KEY_W:
	{
		_keysDown ^= BIT(0);
		break;
	}
	case GLFW_KEY_S:
	{
		_keysDown ^= BIT(1);
		break;
	}
	case GLFW_KEY_A:
	{
		_keysDown ^= BIT(2);
		break;
	}
	case GLFW_KEY_D:
	{
		_keysDown ^= BIT(3);
		break;
	}
	}
	return false;
}

bool CameraPer::handleMouse(double deltaTime)
{
    //check if this is the first time
	if (_mouseState & BIT(0))
	{
		_mouseState |= BIT(0);
		_lastX = _mouseMoved.x;
		_lastY = _mouseMoved.y;
	}

	float xOffset = _mouseMoved.x - _lastX;
	float yOffset = _lastY - _mouseMoved.y; //y is inverted

	_lastX = _mouseMoved.x;
	_lastY = _mouseMoved.y;

	xOffset *= _sensitivity * deltaTime;
	yOffset *= _sensitivity * deltaTime;

	_yaw += xOffset;
	_pitch += yOffset;

	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	direction.y = sin(glm::radians(_pitch));
	direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_cameraFront = glm::normalize(direction);

	return false;
}

}