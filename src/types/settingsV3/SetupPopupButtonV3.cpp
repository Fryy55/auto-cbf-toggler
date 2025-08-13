#include "SetupPopupButtonV3.hpp"

#include "SetupCBFTogglePopup.hpp"

using namespace geode::prelude;


//* Setting
Result<std::shared_ptr<SettingV3>> SetupPopupButtonV3::parse(
	std::string const& key,
	std::string const& modID,
	matjson::Value const& json
) {
	auto ret = std::make_shared<SetupPopupButtonV3>();
	auto root = checkJson(json, "SetupPopupButtonV3");

	ret->init(key, modID);
	ret->parseNameAndDescription(root);

	return root.ok(std::static_pointer_cast<SettingV3>(ret));
}

SettingNodeV3* SetupPopupButtonV3::createNode(float width) {
	return SetupPopupButtonNodeV3::create(
		std::static_pointer_cast<SetupPopupButtonV3>(shared_from_this()),
		width
	);
}

//* SettingNode
SetupPopupButtonNodeV3* SetupPopupButtonNodeV3::create(
	std::shared_ptr<SetupPopupButtonV3> const& setting,
	float width
) {
	auto ret = new SetupPopupButtonNodeV3;

	if (ret->init(setting, width)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool SetupPopupButtonNodeV3::init(
	std::shared_ptr<SetupPopupButtonV3> const& setting,
	float width
) {
	if (!SettingNodeV3::init(setting, width))
		return false;

	auto menu = this->getButtonMenu();
	auto btnSpr = ButtonSprite::create("Edit");

	btnSpr->setScale(0.7f);
	menu->addChildAtPosition(
		CCMenuItemExt::createSpriteExtra(
			btnSpr,
			[](CCMenuItemSpriteExtra*) {
				SetupCBFTogglePopup::create()->show();
			}
		),
		Anchor::Center
	);

	menu->setContentWidth(50.f);
	menu->updateLayout();

	this->updateState(nullptr);

	return true;
}