#pragma once

#include <Geode/cocos/menu_nodes/CCMenu.h>


namespace cbf::utils {
	using SEL_Toggle = void (cocos2d::CCObject::*)(CCMenuItemToggler*);
	#define toggle_selector(...) (cbf::utils::SEL_Toggle)(&__VA_ARGS__)
	cocos2d::CCMenu* createTogglerMenu(
		char const* labelText,
		char const* nodeID,
		bool& dataValue,
		SEL_Toggle togglerCallback,
		cocos2d::CCObject* callbackTarget,
		float labelMaxWidth = 150.f,
		std::optional<char const*> infoText = std::nullopt
	);

	std::optional<std::uint8_t> validatePercentage(
		std::string const& percentageStr,
		std::optional<std::uint8_t> oldPercentage = std::nullopt
	);
}