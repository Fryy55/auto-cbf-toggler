#include "AddPercentagePopup.hpp"

#include "CBFToggleManager.hpp"
#include "utils.hpp"
#include "AddCellEvent.hpp"

using namespace geode::prelude;


AddPercentagePopup* AddPercentagePopup::create() {
	auto ret = new AddPercentagePopup;

	if (ret->initAnchored(230.f, 170.f)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool AddPercentagePopup::setup() {
	this->setTitle("Add Percentage", "goldFont.fnt", 1.f);
	this->setID("AddPercentagePopup");

	m_buttonMenu->removeFromParent();



	auto menu = CCMenu::create();
	menu->setContentSize(m_mainLayer->getContentSize());
	menu->setID("main-menu");
	m_mainLayer->addChildAtPosition(menu, Anchor::Center);


	auto addBtn = CCMenuItemSpriteExtra::create(
		ButtonSprite::create(
			"Add", 75,
			true, "bigFont.fnt",
			"GJ_button_01.png",
			30, 0.8f
		),
		this,
		menu_selector(AddPercentagePopup::onAdd)
	);
	addBtn->setID("add-button");
	menu->addChildAtPosition(addBtn, Anchor::Bottom, { 55.f, 30.f });

	auto cancelBtn = CCMenuItemSpriteExtra::create(
		ButtonSprite::create(
			"Cancel", 75,
			true, "bigFont.fnt",
			"GJ_button_06.png",
			30, 1.f
		),
		this,
		menu_selector(AddPercentagePopup::onClose)
	);
	cancelBtn->setID("cancel-button");
	menu->addChildAtPosition(cancelBtn, Anchor::Bottom, { -55.f, 30.f });


	constexpr float percentageLabelY = 40.f;

	auto percentageLabel = CCLabelBMFont::create("Percentage", "goldFont.fnt");
	percentageLabel->setScale(0.8f);
	percentageLabel->setID("percentage-label");
	m_mainLayer->addChildAtPosition(percentageLabel, Anchor::Left, { 70.f, percentageLabelY });

	m_percentageInput = TextInput::create(160.f, "Percentage");
	m_percentageInput->setCommonFilter(CommonFilter::Uint);
	m_percentageInput->setMaxCharCount(3);
	m_percentageInput->setID("percentage-input");
	menu->addChildAtPosition(m_percentageInput, Anchor::Left, { 95.f, percentageLabelY - 28.f });

	auto clearPercentageBtnTopSpr = CCSprite::createWithSpriteFrameName("GJ_deleteIcon_001.png");
	auto clearPercentageBtnSpr = ButtonSprite::create(
		clearPercentageBtnTopSpr,
		40.f,
		true,
		40.f,
		"GJ_button_04.png",
		1.f
	);
	clearPercentageBtnTopSpr->setPositionY(20.f);
	clearPercentageBtnSpr->setScale(0.8f);
	auto clearPercentageBtn = CCMenuItemExt::createSpriteExtra(
		clearPercentageBtnSpr,
		[this](CCMenuItemSpriteExtra*) {
			m_percentageInput->setString("");
		}
	);
	clearPercentageBtn->setID("clear-percentage-button");
	menu->addChildAtPosition(clearPercentageBtn, Anchor::Right, { -30.f, percentageLabelY - 28.f });


	constexpr float toggleLabelY = 66.f;

	auto toggleLabel = CCLabelBMFont::create("Toggle", "goldFont.fnt");
	toggleLabel->setScale(0.8f);
	toggleLabel->setID("on-label");
	m_mainLayer->addChildAtPosition(toggleLabel, Anchor::BottomLeft, { 48.f, toggleLabelY });

	auto onSpr = CCLabelBMFont::create("On", "bigFont.fnt");
	onSpr->setColor({ 0, 255, 0 });
	onSpr->setScale(0.7f);
	onSpr->setID("on-sprite");
	auto offSpr = CCLabelBMFont::create("Off", "bigFont.fnt");
	offSpr->setColor({ 255, 0, 0 });
	offSpr->setScale(0.7f);
	offSpr->setID("off-sprite");
	m_onToggler = CCMenuItemExt::createToggler(
		onSpr, offSpr,
		[](CCMenuItemToggler*) {}
	);
	m_onToggler->setID("on-toggler");
	menu->addChildAtPosition(m_onToggler, Anchor::BottomLeft, { 115.f, toggleLabelY });

	return true;
}

void AddPercentagePopup::keyDown(enumKeyCodes key) {
	switch (key) {
		case KEY_Escape:
			if (CBFToggleManager::get()->getData().addOnEscape)
				this->onAdd(nullptr);
			else
				this->onClose(nullptr);
			break;

		default:
			break;
	}

	return;
}

void AddPercentagePopup::onAdd(CCObject*) {
	auto percentageOpt = cbf::utils::validatePercentage(m_percentageInput->getString());
	if (!percentageOpt)
		return;

	std::uint8_t percentage = percentageOpt.value();

	AddCellEvent(percentage, m_onToggler->isOn()).post();

	onClose(nullptr);

	return;
}