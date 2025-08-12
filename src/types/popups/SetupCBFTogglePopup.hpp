#pragma once

#include <Geode/ui/Popup.hpp>

#include "LimitedTextArea.hpp"
#include "UpdateListStateEvent.hpp"
#include "AddCellEvent.hpp"


class SetupCBFTogglePopup final : public geode::Popup<> {
public:
	static SetupCBFTogglePopup* create();

private:
	bool setup() override;

	void onToggle(CCMenuItemToggler*);
	void onIndicator(CCMenuItemToggler*);
	void onAddOnEsc(CCMenuItemToggler*);


	// List
	void updateState();
	void addCell(std::uint8_t, bool);

	void onAdd(cocos2d::CCObject*);
	void onDeleteAll(cocos2d::CCObject*);

	geode::ListenerResult onUpdateStateEvent(UpdateListStateEvent*);
	geode::ListenerResult onAddCellEvent(AddCellEvent*);

	// Fields
	geode::ScrollLayer* m_scrollLayer;
	cocos2d::CCLabelBMFont* m_emptyListLabel;
	LimitedTextArea* m_percentageCountLabel;

	geode::EventListener<geode::EventFilter<UpdateListStateEvent>> m_updateListener {
		this,
		&SetupCBFTogglePopup::onUpdateStateEvent
	};
	geode::EventListener<geode::EventFilter<AddCellEvent>> m_addCellListener {
		this,
		&SetupCBFTogglePopup::onAddCellEvent
	};

	static constexpr cocos2d::CCSize s_listContentSize { 270.f, 120.f };
};