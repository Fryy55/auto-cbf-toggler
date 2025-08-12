#pragma once

#include <Geode/ui/Popup.hpp>

#include "PercentageCell.hpp"


class EditPercentagePopup final : public geode::Popup<PercentageCell*> {
public:
	static EditPercentagePopup* create(PercentageCell* cell);

private:
	bool setup(PercentageCell*) override;

	void keyDown(cocos2d::enumKeyCodes) override;

	void onConfirm(cocos2d::CCObject*);

	// Fields
	LimitedTextArea* m_percentageField;
	CCMenuItemToggler* m_onDisplay;

	geode::TextInput* m_percentageInput;
	CCMenuItemToggler* m_onToggler;
};