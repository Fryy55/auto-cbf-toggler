#pragma once

#include <Geode/loader/Event.hpp>


struct AddCellEvent final : geode::Event {
	AddCellEvent(std::uint8_t percentage, bool on) : percentage(percentage), on(on) {}

	std::uint8_t percentage;
	bool on;
};