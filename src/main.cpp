#include <Geode/Geode.hpp>

#include "SetupPopupButtonV3.hpp"
#include "ResetTitleV3.hpp"

using namespace geode::prelude;


$on_mod(Loaded) {
	static_cast<void>(Mod::get()->registerCustomSettingType(
		"setup-popup-button",
		SetupPopupButtonV3::parse
	));
	static_cast<void>(Mod::get()->registerCustomSettingType(
		"reset-title",
		ResetTitleV3::parse
	));
}