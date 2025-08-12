#pragma once

#include <Geode/loader/Event.hpp>


struct UpdateListStateEvent final : geode::Event {
	UpdateListStateEvent() : geode::Event() {}
};