#pragma once
#include "Event.hpp"
#include <glm/glm.hpp>

namespace Engine
{
namespace Events
{
    class MouseMovedEvent : public BasicEvent
{
public:
	MouseMovedEvent(double xpos, double ypos) noexcept
		:_pos{xpos, ypos}
	{};

	const glm::vec2& getPos() const noexcept { return _pos; };

	EVENT_TYPE(MouseMoved);

private:
	glm::vec2 _pos;
};

} // NAMESPACE EVENTS
} // NAMESPACE ENGINE

