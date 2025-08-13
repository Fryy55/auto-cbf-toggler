#include "ResetTitleV3.hpp"

#include "CBFToggleManager.hpp"
#include "QuickNotification.hpp"

using namespace geode::prelude;


//* Setting
Result<std::shared_ptr<SettingV3>> ResetTitleV3::parse(
	std::string const& key,
	std::string const& modID,
	matjson::Value const& json
) {
	auto ret = std::make_shared<ResetTitleV3>();
	auto root = checkJson(json, "ResetTitleV3");

	ret->init(key, modID);
	ret->parseNameAndDescription(root);

	return root.ok(std::static_pointer_cast<SettingV3>(ret));
}

void ResetTitleV3::reset() {
	std::filesystem::remove(Mod::get()->getSaveDir()/"data.json");

	CBFToggleManager::get()->loadData();

	QuickNotification::create("Data reset!", NotificationIcon::Success, 0.5f)->show();

	return;
}

SettingNodeV3* ResetTitleV3::createNode(float width) {
	return ResetTitleNodeV3::create(
		std::static_pointer_cast<ResetTitleV3>(shared_from_this()),
		width
	);
}

//* SettingNode
ResetTitleNodeV3* ResetTitleNodeV3::create(
	std::shared_ptr<ResetTitleV3> const& setting,
	float width
) {
	auto ret = new ResetTitleNodeV3;

	if (ret->init(setting, width)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool ResetTitleNodeV3::init(
	std::shared_ptr<ResetTitleV3> const& setting,
	float width
) {
	if (!SettingNodeV3::init(setting, width))
		return false;

	auto menu = this->getButtonMenu();
	this->getNameLabel()->setVisible(false);

	auto const menuCW = this->getContentWidth() - 20.f;

	auto label = CCLabelBMFont::create(this->getSetting()->getDisplayName().c_str(), "goldFont.fnt");
	label->limitLabelWidth(menuCW, 5.f, 0.1f);

	menu->setPositionX(10.f);
	menu->setAnchorPoint({ 0.f, 0.5f });
	menu->setContentWidth(menuCW);

	menu->addChildAtPosition(label, Anchor::Center);

	this->updateState(nullptr);

	return true;
}