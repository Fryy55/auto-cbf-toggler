#include <Geode/modify/PauseLayer.hpp>

#include "SetupCBFTogglePopup.hpp"

using namespace geode::prelude;


class $modify(PauseLayer) {
	$override
	void customSetup() {
		PauseLayer::customSetup();

		auto menu = this->getChildByID("right-button-menu");

		auto spr = CircleButtonSprite::createWithSpriteFrameName(
			"popup_button_icon.png"_spr,
			1.f,
			CircleBaseColor::Green,
			CircleBaseSize::Small
		);
		spr->setScale(0.8f);
		auto button = CCMenuItemExt::createSpriteExtra(
			spr,
			[](CCMenuItemSpriteExtra*) {
				SetupCBFTogglePopup::create()->show();
			}
		);
		button->setID("setup-cbf-toggler-button"_spr);

		menu->addChild(button);
		menu->updateLayout();

		return;
	}
};