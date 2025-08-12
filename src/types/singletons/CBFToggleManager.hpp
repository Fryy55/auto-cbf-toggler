#pragma once

#include <map>


class CBFToggleManager final {
public:
	static CBFToggleManager* get();

private:
	CBFToggleManager();

public:
	[[nodiscard]] std::map<std::uint8_t, bool>* getDB() const { return m_db; }
	[[nodiscard]] bool getDebugLabelSetting() const { return m_debugLabel; }

	void updateSettings();


	CBFToggleManager(CBFToggleManager const&) = delete;
	CBFToggleManager(CBFToggleManager&&) = delete;
	CBFToggleManager& operator=(CBFToggleManager const&) = delete;
	CBFToggleManager& operator=(CBFToggleManager&&) = delete;

private:
	// Fields
	std::map<std::uint8_t, bool>* m_db;
	bool m_debugLabel;
};