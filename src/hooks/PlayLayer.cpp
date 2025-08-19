#include <Geode/modify/PlayLayer.hpp>

#include "CBFToggleManager.hpp"

using namespace geode::prelude;


class $modify(HPlayLayer, PlayLayer) {
	struct Fields {
		std::unordered_map<std::uint8_t, bool> m_map{};
		CCSprite* m_indicator = nullptr;

		Mod* m_cbf = Loader::get()->getLoadedMod("syzzi.click_between_frames");

		bool& m_enabled = CBFToggleManager::get()->getData().enabled;
		bool& m_showIndicator = CBFToggleManager::get()->getData().showIndicator;

		bool m_wasOn = false;
	};

	$override
	bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
		if (!PlayLayer::init(level, useReplay, dontCreateObjects))
			return false;

		auto indicator = CCSprite::createWithSpriteFrameName("uiDot_001.png");
		auto winSize = CCDirector::get()->getWinSize();
		indicator->CCNode::setPosition(winSize.width, winSize.height);
		indicator->setAnchorPoint({ 1.f, 1.f });
		indicator->setScale(1.5f);
		indicator->setOpacity(0);
		indicator->setID("indicator"_spr);

		this->addChild(indicator);
		m_fields->m_indicator = indicator;

		return true;
	}

	$override
	void resetLevel() {
		PlayLayer::resetLevel();

		m_fields->m_map.clear();

		if (!m_fields->m_enabled)
			return;

		for (auto const& [percentage, on] : CBFToggleManager::get()->getData().db)
			m_fields->m_map.emplace(percentage, on);

		return;
	}

	$override
	float getCurrentPercent() {
		float percentage = PlayLayer::getCurrentPercent();

		if (!m_fields->m_enabled || !m_fields->m_indicator) // getCurrentPercent is called in init
			return percentage;


		if (m_fields->m_map.contains(percentage)) {
			m_fields->m_wasOn = true;

			bool on = m_fields->m_map[percentage];

			m_fields->m_cbf->setSettingValue("soft-toggle", !on);

			if (m_fields->m_showIndicator) {
				auto indicator = m_fields->m_indicator;

				indicator->stopAllActions();
				indicator->setColor(on ? ccc3(0, 255, 0) : ccc3(255, 0, 0));
				indicator->setOpacity(200);

				indicator->runAction(CCFadeTo::create(0.3f, 0));
			}

			m_fields->m_map.erase(percentage);
		}

		return percentage;
	}
};


#include <Geode/modify/EndLevelLayer.hpp>

class $modify(EndLevelLayer) {
	$override
	void customSetup() {
		EndLevelLayer::customSetup();

		bool& wasOn = static_cast<HPlayLayer*>(m_playLayer)->m_fields->m_wasOn;

		if (wasOn) {
			auto hideSpr = this->querySelector("hide-button")->getChildByType<CCSprite>(0);
			hideSpr->stopAllActions();
			hideSpr->setOpacity(125);
		}

		wasOn = false;

		return;
	}
};