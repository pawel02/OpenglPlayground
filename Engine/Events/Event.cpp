#include "Event.hpp"
namespace Engine
{
namespace Events
{
    std::unordered_map<std::type_index, EventBus::EventVector*> EventBus::_subscribers;
}
}