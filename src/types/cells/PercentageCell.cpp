#include "PercentageCell.hpp"

#include "CBFToggleManager.hpp"
#include "EditPercentagePopup.hpp"
#include "UpdateListStateEvent.hpp"

using namespace geode::prelude;


PercentageCell* PercentageCell::create(std::uint8_t percentage, bool on, float width) {
	auto ret = new PercentageCell;

	if (ret->init(percentage, on, width)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool PercentageCell::init(std::uint8_t percentage, bool on, float width) {
	if (!CCLayerColor::initWithColor({ 0, 0, 0, 0 }, width, s_height))
		return false;

	this->setTag(percentage);



	CBFToggleManager::get()->getData().db.emplace(percentage, on);



	auto percentageLabel = CCLabelBMFont::create("Percentage", "goldFont.fnt");
	percentageLabel->setScale(0.5f);
	percentageLabel->setID("percentage-label");
	this->addChildAtPosition(percentageLabel, Anchor::TopLeft, { 45.f, -7.f });


	m_percentageField = LimitedTextArea::create({ 82.5f, 30.f }, numToString(percentage));
	m_percentageField->setScale(0.67f);
	m_percentageField->setID("percentage-field");
	this->addChildAtPosition(m_percentageField, Anchor::BottomLeft, { 17.f, 1.5f });



	constexpr float cbfX = 125.f;

	auto cbfLabel = CCLabelBMFont::create("CBF", "goldFont.fnt");
	cbfLabel->setScale(0.5f);
	cbfLabel->setID("cbf-label");
	this->addChildAtPosition(cbfLabel, Anchor::TopLeft, { cbfX, -7.f });


	auto onSpr = CCLabelBMFont::create("On", "bigFont.fnt");
	onSpr->setColor({ 0, 255, 0 });
	onSpr->setID("on-sprite");
	auto offSpr = CCLabelBMFont::create("Off", "bigFont.fnt");
	offSpr->setColor({ 255, 0, 0 });
	offSpr->setID("off-sprite");
	m_onDisplay = CCMenuItemExt::createToggler(
		onSpr, offSpr,
		[](CCMenuItemToggler*) {}
	);
	m_onDisplay->setScale(0.7f);
	m_onDisplay->setClickable(false);
	m_onDisplay->toggle(on);
	m_onDisplay->setID("on-display");
	this->addChildAtPosition(m_onDisplay, Anchor::BottomLeft, { cbfX, 13.f });



	auto menu = CCMenu::create();
	menu->setContentSize({ 75.f, s_height });
	menu->setScale(0.8f);
	menu->setID("menu");
	this->addChildAtPosition(
		menu,
		Anchor::Right,
		{ -(menu->getContentWidth() / 2.f) - 7.f, 0.f }
	);

	menu->setLayout(RowLayout::create());


	auto editBtn = CCMenuItemSpriteExtra::create(
		CCSprite::createWithSpriteFrameName("GJ_viewLevelsBtn_001.png"),
		this,
		menu_selector(PercentageCell::onEdit)
	);
	editBtn->setID("edit-button");
	menu->addChild(editBtn);


	auto deleteBtn = CCMenuItemSpriteExtra::create(
		CircleButtonSprite::createWithSpriteFrameName("edit_delBtn_001.png", 0.8f),
		this,
		menu_selector(PercentageCell::onDelete)
	);
	deleteBtn->setID("delete-button");
	menu->addChild(deleteBtn);


	menu->updateLayout();

	return true;
}

void PercentageCell::onDelete(CCObject*) {
	CBFToggleManager::get()->getData().db.erase(this->getTag());
	this->removeFromParent();

	UpdateListStateEvent().post();

	return;
}

void PercentageCell::onEdit(CCObject*) {
	EditPercentagePopup::create(this)->show();

	return;
}