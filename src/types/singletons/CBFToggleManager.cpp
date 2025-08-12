#include "CBFToggleManager.hpp"

#include <Geode/Geode.hpp>

using namespace geode::prelude;


CBFToggleManager* CBFToggleManager::get() {
	static auto instance = CBFToggleManager();

	return &instance;
}

CBFToggleManager::CBFToggleManager() {
	m_db = new std::map<std::uint8_t, bool>;

	// default init
	m_debugLabel = false;

	log::info("Manager initialized.");
}

void CBFToggleManager::updateSettings() {
	m_debugLabel = Mod::get()->getSettingValue<bool>("debug-label");

	return;
}