#pragma once
#include "Event.hpp"
#include <glm/glm.hpp>

namespace Engine
{
namespace Events
{
class WindowCloseEvent : public BasicEvent
{
public:
	WindowCloseEvent() noexcept
	{}
	EVENT_TYPE(WindowClose);
};

class WindowResizeEvent : public BasicEvent
{

public:
	WindowResizeEvent(int w, int h) noexcept
		:size{w, h}
	{}

	const glm::vec2& getSize() const noexcept { return size;  }

	EVENT_TYPE(WindowResize);

private:
	glm::vec2 size;
};

}
}
