#pragma once

#include "SaveData.hpp"


class CBFToggleManager final {
public:
	static CBFToggleManager* get();

private:
	CBFToggleManager();

public:
	[[nodiscard]] SaveData& getData() { return m_data; }

	void saveData() const;
	//! use very sparingly!!!!! pretty much should only be used in a ctor
	void loadData();


	CBFToggleManager(CBFToggleManager const&) = delete;
	CBFToggleManager(CBFToggleManager&&) = delete;
	CBFToggleManager& operator=(CBFToggleManager const&) = delete;
	CBFToggleManager& operator=(CBFToggleManager&&) = delete;

private:
	// Fields
	SaveData m_data{};
};