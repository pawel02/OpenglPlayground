#pragma once
#include "Event.hpp"

namespace Engine
{
namespace Events
{
    class KeyPressedEvent : public BasicEvent
    {
    public:
        KeyPressedEvent(int keyCode) noexcept
            :_keyCode{keyCode}
        {};

        const int& getCode() const noexcept { return _keyCode; };

        EVENT_TYPE(KeyPressed);

    private:
        int _keyCode;
    };

    class KeyReleasedEvent : public BasicEvent
    {
    public:
        KeyReleasedEvent(int keyCode) noexcept
            :_keyCode{ keyCode }
        {};

        const int& getCode() const noexcept { return _keyCode; };

        EVENT_TYPE(KeyPressed);

    private:
        int _keyCode;
    };
} //NAMESPACE EVENTS
} // NAMESPACE ENGINE
