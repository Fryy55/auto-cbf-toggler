#include <Geode/loader/SettingV3.hpp>


class ResetTitleV3 final : public geode::SettingV3 {
public:
	static geode::Result<std::shared_ptr<geode::SettingV3>> parse(
		std::string const&,
		std::string const&,
		matjson::Value const&
	);

	bool load(matjson::Value const&) override { return true; }
	bool save(matjson::Value&) const override { return true; }

	bool isDefaultValue() const override { return true; }
	void reset() override;

	geode::SettingNodeV3* createNode(float) override;
};


class ResetTitleNodeV3 final : public geode::SettingNodeV3 {
public:
	static ResetTitleNodeV3* create(std::shared_ptr<ResetTitleV3> const&, float);

private:
	bool init(std::shared_ptr<ResetTitleV3> const&, float);

public:
	void onCommit() override {}
	void onResetToDefault() override {};

	[[nodiscard]] bool hasUncommittedChanges() const override { return false; }
	[[nodiscard]] bool hasNonDefaultValue() const override { return false; }
};