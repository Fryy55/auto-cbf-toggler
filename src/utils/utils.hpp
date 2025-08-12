#pragma once

#include <Geode/cocos/menu_nodes/CCMenu.h>


namespace cbf::utils {
	cocos2d::CCMenu* createTogglerMenu(
		char const* labelText,
		char const* nodeID,
		std::function<void (CCMenuItemToggler*)> togglerCallback,
		float labelMaxWidth = 150.f,
		std::optional<char const*> infoText = std::nullopt
	);

	std::optional<std::uint8_t> validatePercentage(
		std::string const& percentageStr,
		std::optional<std::uint8_t> oldPercentage = std::nullopt
	);
}