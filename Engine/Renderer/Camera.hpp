#pragma once
#include <vector>
#include <glm/glm.hpp>

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
class Camera
{
public:
	Camera(glm::mat4 proj) noexcept
		:_projection{proj}
	{}
	virtual ~Camera() noexcept {};

	virtual void onUpdate(float deltaTime) = 0;
	virtual const cameraMatricies getMatricies() const noexcept { return{ _projection, _view}; }
protected:
    glm::mat4 _projection;
	glm::mat4 _view = glm::mat4{1.0f};
};

}