#pragma once

#include <Geode/ui/Popup.hpp>


class AddPercentagePopup final : public geode::Popup<> {
public:
	static AddPercentagePopup* create();

private:
	bool setup() override;

	void keyDown(cocos2d::enumKeyCodes) override;

	void onAdd(cocos2d::CCObject*);

	// Fields
	geode::TextInput* m_percentageInput;
	CCMenuItemToggler* m_onToggler;
};