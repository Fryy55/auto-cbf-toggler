#pragma once

#include <map>

#include <matjson.hpp>

#include "constants.hpp"


struct SaveData final {
	using Database = std::map<std::uint8_t, bool>;
	Database db = {};

	bool enabled = constants::defaults::enabled;

	bool showIndicator = constants::defaults::showIndicator;
	bool addOnEscape = constants::defaults::addOnEscape;
	bool debugLabel = constants::defaults::debugLabel;
};


template <>
struct matjson::Serialize<SaveData::Database> {
	// Err - db with skipped values
	static geode::Result<SaveData::Database, SaveData::Database> fromJson(matjson::Value const&);

	static matjson::Value toJson(SaveData::Database const&);
};

template <>
struct matjson::Serialize<SaveData> {
	// doesn't return Err, fills in defaults instead
	static geode::Result<SaveData> fromJson(matjson::Value const&);

	static matjson::Value toJson(SaveData const&);
};