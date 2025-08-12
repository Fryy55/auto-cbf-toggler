#include "SaveData.hpp"

#include <Geode/utils/string.hpp>
#include <Geode/ui/Notification.hpp>

#include "DelayedNotifsManager.hpp"

using namespace geode::prelude;


//* SaveData::Database
Result<SaveData::Database, SaveData::Database> matjson::Serialize<SaveData::Database>::fromJson(
	matjson::Value const& json
) {
	SaveData::Database db{};
	bool failed = false;

	for (auto const& [percentageStr, onValue] : json) {
		auto percentageRes = numFromString<std::uint8_t>(percentageStr);
		auto onRes = onValue.asBool();

		if (percentageRes && onRes)
			db.emplace(percentageRes.unwrap(), onRes.unwrap());
		else
			failed = true;
	}

	if (failed)
		return Err(std::move(db));
	else
		return Ok(std::move(db));
}

matjson::Value matjson::Serialize<SaveData::Database>::toJson(SaveData::Database const& database) {
	std::unordered_map<std::string, bool> map{};

	for (auto const& [percentage, on] : database) {
		map.emplace(numToString(percentage), on);
	}

	return { std::move(map) };
}

//* SaveData
Result<SaveData> matjson::Serialize<SaveData>::fromJson(matjson::Value const& json) {
	SaveData data{};


	auto dbRes = json["db"].as<SaveData::Database>();
	if (dbRes)
		data.db = std::move(dbRes.unwrap());
	else {
		data.db = std::move(dbRes.unwrapErr());
		DelayedNotifsManager::get()->add(Notification::create(
			"Failed to parse some of the database values!",
			NotificationIcon::Warning,
			3.f
		));
		log::warn("Failed to parse some of the database values.");
	}


	bool settingsFailed = false;

	data.enabled = json["enabled"].asBool().unwrapOrElse([&settingsFailed]() {
		settingsFailed = true;

		return constants::defaults::enabled;
	});

	data.showIndicator = json["showIndicator"].asBool().unwrapOrElse([&settingsFailed]() {
		settingsFailed = true;

		return constants::defaults::showIndicator;
	});
	data.addOnEscape = json["addOnEscape"].asBool().unwrapOrElse([&settingsFailed]() {
		settingsFailed = true;

		return constants::defaults::addOnEscape;
	});
	data.debugLabel = json["debugLabel"].asBool().unwrapOrElse([&settingsFailed]() {
		settingsFailed = true;

		return constants::defaults::debugLabel;
	});

	if (settingsFailed) {
		DelayedNotifsManager::get()->add(Notification::create(
			" Failed to parse some of the settings!\n"
			" Using default values for them",
			NotificationIcon::Warning,
			3.f
		));
		log::warn("Failed to parse some of the settings. Using defaults.");
	}

	log::debug("SaveData deserialized.");

	return Ok(std::move(data));
}

matjson::Value matjson::Serialize<SaveData>::toJson(SaveData const& data) {
	log::debug("SaveData serialized.");

	return matjson::makeObject({
		{ "db", data.db },

		{ "enabled", data.enabled },

		{ "showIndicator", data.showIndicator },
		{ "addOnEscape", data.addOnEscape },
		{ "debugLabel", data.debugLabel }
	});
}