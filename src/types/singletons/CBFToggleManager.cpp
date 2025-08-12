#include "CBFToggleManager.hpp"

#include <Geode/Geode.hpp>

#include "DelayedNotifsManager.hpp"

using namespace geode::prelude;


CBFToggleManager* CBFToggleManager::get() {
	static auto instance = CBFToggleManager();

	return &instance;
}

CBFToggleManager::CBFToggleManager() {
	loadData();
	DelayedNotifsManager::get()->fire();

	log::info("Manager initialized.");
}

void CBFToggleManager::saveData() const {
	if (
		!file::writeStringSafe(
			Mod::get()->getSaveDir()/"data.json",
			matjson::Value(m_data).dump(matjson::TAB_INDENTATION)
		)
	) {
		log::error("Failed to write save data.");
		Notification::create("Failed to write save data.", NotificationIcon::Error)->show();
	}

	return;
}

void CBFToggleManager::loadData() {
	auto filePath = Mod::get()->getSaveDir()/"data.json";

	if (!std::filesystem::exists(filePath)) {
		log::info("No file found, using defaults.");
		return;
	}


	if (GEODE_UNWRAP_IF_OK(json, file::readJson(filePath))) {
		m_data = json.as<SaveData>().unwrap(); // never returns Err
	} else {
		log::error("Error parsing data, using defaults.");
		DelayedNotifsManager::get()->add(
			Notification::create("Error parsing data, using defaults.", NotificationIcon::Error, 3.f)
		);
	}

	return;
}