#include "SetupCBFTogglePopup.hpp"

#include "CBFToggleManager.hpp"
#include "utils.hpp"
#include "PercentageCell.hpp"
#include "AddPercentagePopup.hpp"

using namespace geode::prelude;


SetupCBFTogglePopup* SetupCBFTogglePopup::create() {
	auto ret = new SetupCBFTogglePopup;

	if (ret->initAnchored(360.f, 280.f)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool SetupCBFTogglePopup::setup() {
	this->setTitle("Auto CBF Toggler", "goldFont.fnt", 0.9f);
	this->setID("SetupCBFTogglePopup"_spr);
	m_buttonMenu->setID("close-menu");

	CBFToggleManager::get()->updateSettings();



	auto enableMenu = cbf::utils::createTogglerMenu(
		"Enabled",
		"enable",
		[this](CCMenuItemToggler* toggler) {
			onToggle(toggler);
		}
	);
	enableMenu->setScale(0.7f);
	m_mainLayer->addChildAtPosition(enableMenu, Anchor::Top, { 0.f, -50.f });



	auto percentagesList = CCLayerColor::create({ 0, 0, 0, 90 });
	percentagesList->setContentSize(s_listContentSize);
	percentagesList->ignoreAnchorPointForPosition(false);
	percentagesList->setID("percentages-list");
	m_mainLayer->addChildAtPosition(percentagesList, Anchor::Center, { -30.f, 12.f });

	m_scrollLayer = ScrollLayer::create(s_listContentSize);
	m_scrollLayer->m_contentLayer->setLayout(
		ColumnLayout::create()
			->setGap(0.f)
			->setAxisReverse(true)
			->setAxisAlignment(AxisAlignment::End)
			->setAutoGrowAxis(percentagesList->getContentHeight())
	);
	m_scrollLayer->setID("scroll-layer");
	percentagesList->addChild(m_scrollLayer);

	auto borders = ListBorders::create();
	borders->setContentSize(s_listContentSize);
	borders->ignoreAnchorPointForPosition(true);
	borders->setID("borders");
	percentagesList->addChild(borders);

	m_emptyListLabel = CCLabelBMFont::create("Nothing here...", "bigFont.fnt");
	m_emptyListLabel->setPosition(s_listContentSize / 2.f);
	m_emptyListLabel->setScale(0.7f);
	m_emptyListLabel->setID("empty-list-label");
	percentagesList->addChild(m_emptyListLabel);


	auto listButtonsMenu = CCMenu::create();
	listButtonsMenu->setContentSize(s_listContentSize);
	listButtonsMenu->setLayout(
		ColumnLayout::create()
			->setAxisReverse(true)
			->setCrossAxisOverflow(false)
			->setGap(9.f)
			->setAutoScale(false)
	);
	listButtonsMenu->setContentWidth(65.f);
	listButtonsMenu->setPosition(s_listContentSize.width, 0.f);
	listButtonsMenu->ignoreAnchorPointForPosition(true);
	listButtonsMenu->setID("list-buttons-menu");
	percentagesList->addChild(listButtonsMenu);

	auto addBtnSpr = CCSprite::createWithSpriteFrameName("GJ_plusBtn_001.png");
	addBtnSpr->setScale(0.83f);
	auto addBtn = CCMenuItemSpriteExtra::create(
		addBtnSpr,
		this,
		menu_selector(SetupCBFTogglePopup::onAdd)
	);
	addBtn->setID("add-button");
	listButtonsMenu->addChild(addBtn);

	auto deleteAllBtn = CCMenuItemSpriteExtra::create(
		CCSprite::createWithSpriteFrameName("GJ_trashBtn_001.png"),
		this,
		menu_selector(SetupCBFTogglePopup::onDeleteAll)
	);
	deleteAllBtn->setID("delete-all-button");
	listButtonsMenu->addChild(deleteAllBtn);

	m_percentageCountLabel = LimitedTextArea::create(
		{ 80.f, 30.f },
		"",
		16,
		"bigFont.fnt",
		{ 0.f, 2.f },
		{ 0, 0, 0, 70 }
	);
	m_percentageCountLabel->setScale(0.45f);
	m_percentageCountLabel->setID("percentage-count-label");
	listButtonsMenu->addChild(m_percentageCountLabel);

	listButtonsMenu->updateLayout();


	// add children if db has them on init
	for (auto const& [percentage, on] : *CBFToggleManager::get()->getDB())
		m_scrollLayer->m_contentLayer->addChild(PercentageCell::create(percentage, on, s_listContentSize.width));


	this->updateState();



	constexpr float settingsMenuCH = 60.f;
	constexpr float settingsMenuY = 10.f;

	auto settingsLabel = CCLabelBMFont::create("Settings", "goldFont.fnt");
	settingsLabel->setID("settings-label");
	m_mainLayer->addChildAtPosition(
		settingsLabel,
		Anchor::Bottom,
		{ 0.f, settingsMenuY + settingsMenuCH + 10.f, }
	);


	auto settingsMenu = CCMenu::create();
	settingsMenu->setLayout(
		RowLayout::create()
			->setGrowCrossAxis(true)
			->setCrossAxisOverflow(false)
	);
	settingsMenu->setContentSize(
		{ m_mainLayer->getContentWidth() - 30.f, settingsMenuCH }
	);
	settingsMenu->setAnchorPoint({ 0.5f, 0.f });
	settingsMenu->setID("settings-menu");
	m_mainLayer->addChildAtPosition(settingsMenu, Anchor::Bottom, { 0.f, settingsMenuY });

	settingsMenu->addChild(
		cbf::utils::createTogglerMenu(
			"Show indicator",
			"indicator",
			[this](CCMenuItemToggler* toggler) {
				onIndicator(toggler);
			},
			150.f,
			"Shows a small <cf>indicator</c> whenever <cc>CBF</c> gets toggled <cg>on</c> or <cr>off</c>"
		)
	);
	#ifdef GEODE_DESKTOP
		settingsMenu->addChild(
			cbf::utils::createTogglerMenu(
				"Add on Escape",
				"add-on-esc",
				[this](CCMenuItemToggler* toggler) {
					onAddOnEsc(toggler);
				},
				150.f,
				"<cb>PC-only</c>\n"
				"Toggles whether clicking <cj>Escape</c> <cg>Adds</c> percentage or <cr>Cancels</c> the popup"
			)
		);
	#endif


	settingsMenu->updateLayout();

	return true;
}

void SetupCBFTogglePopup::onToggle(CCMenuItemToggler* toggler) {


	return;
}

void SetupCBFTogglePopup::onIndicator(CCMenuItemToggler* toggler) {


	return;
}

void SetupCBFTogglePopup::onAddOnEsc(CCMenuItemToggler* toggler) {


	return;
}

// List
void SetupCBFTogglePopup::updateState() {
	m_emptyListLabel->setOpacity(
		m_scrollLayer->m_contentLayer->getChildrenCount() ?
			0
			:
			255
	);

	m_percentageCountLabel->setText(
		CBFToggleManager::get()->getDebugLabelSetting() ?
			fmt::format(
				"{}/{}",
				m_scrollLayer->m_contentLayer->getChildrenCount(),
				CBFToggleManager::get()->getDB()->size()
			)
			:
			numToString<std::uint32_t>(m_scrollLayer->m_contentLayer->getChildrenCount())
	);

	bool dark = true;
	for (auto cell : CCArrayExt<PercentageCell>(m_scrollLayer->m_contentLayer->getChildren())) {
		cell->setBGColor(dark);

		dark = !dark;
	}

	m_scrollLayer->m_contentLayer->updateLayout();

	m_scrollLayer->scrollToTop();

	return;
}

void SetupCBFTogglePopup::addCell(std::uint8_t percentage, bool on) {
	CBFToggleManager::get()->getDB()->insert({ percentage, on });

	CCNode* beforeNode = nullptr;
	for (auto node : CCArrayExt<CCNode*>(m_scrollLayer->m_contentLayer->getChildren())) {
		if (node->getTag() > percentage) {
			beforeNode = node;
			break;
		}
	}

	auto cell = PercentageCell::create(percentage, on, s_listContentSize.width);
	if (!beforeNode) // if `node` is the highest percentage
		m_scrollLayer->m_contentLayer->addChild(cell);
	else
		m_scrollLayer->m_contentLayer->insertBefore(cell, beforeNode);

	this->updateState();

	return;
}

void SetupCBFTogglePopup::onAdd(CCObject*) {
	AddPercentagePopup::create()->show();

	return;
}

void SetupCBFTogglePopup::onDeleteAll(CCObject*) {
	createQuickPopup(
		"Reset percentages",
		"Are you sure you want to clear <cr>all</c> percentages?",
		"Cancel", "Yes",
		[this](auto, bool yes) {
			if (yes) {
				m_scrollLayer->m_contentLayer->removeAllChildren();
				CBFToggleManager::get()->getDB()->clear();

				this->updateState();
			}
		}
	);

	return;
}

ListenerResult SetupCBFTogglePopup::onUpdateStateEvent(UpdateListStateEvent*) {
	this->updateState();

	return ListenerResult::Stop;
}

ListenerResult SetupCBFTogglePopup::onAddCellEvent(AddCellEvent* event) {
	this->addCell(event->percentage, event->on);

	return ListenerResult::Stop;
}