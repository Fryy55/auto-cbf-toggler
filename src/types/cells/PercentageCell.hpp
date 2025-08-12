#pragma once

#include <Geode/cocos/layers_scenes_transitions_nodes/CCLayer.h>

#include "LimitedTextArea.hpp"


class PercentageCell final : public cocos2d::CCLayerColor {
public:
	static PercentageCell* create(std::uint8_t percentage, bool on, float width);

private:
	bool init(std::uint8_t, bool, float);


public:
	void setBGColor(bool dark) { this->setOpacity(dark ? 60 : 20); }
	[[nodiscard]] std::pair<LimitedTextArea*, CCMenuItemToggler*> getFields() const { return { m_percentageField, m_onDisplay }; }

private:
	void onEdit(cocos2d::CCObject*);
	void onDelete(cocos2d::CCObject*);

	// Fields
	LimitedTextArea* m_percentageField;
	CCMenuItemToggler* m_onDisplay;

	static constexpr float s_height = 35.f;
};