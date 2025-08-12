#include "utils.hpp"

#include "QuickNotification.hpp"
#include "CBFToggleManager.hpp"

using namespace geode::prelude;


CCMenu* cbf::utils::createTogglerMenu(
	char const* labelText,
	char const* nodeID,
	std::function<void (CCMenuItemToggler*)> togglerCallback,
	float labelMaxWidth,
	std::optional<char const*> infoText
) {
	auto togglerMenu = CCMenu::create();
	constexpr float gap = 5.f;
	togglerMenu->setLayout(
		RowLayout::create()
			->setAutoScale(false)
			->setGap(gap)
	);
	togglerMenu->setID(fmt::format("{}-menu", nodeID));

	auto toggler = CCMenuItemExt::createTogglerWithStandardSprites(
		1.f,
		std::move(togglerCallback)
	);
	toggler->setID(fmt::format("{}-toggler", nodeID));
	togglerMenu->addChild(toggler);

	auto label = CCLabelBMFont::create(labelText, "bigFont.fnt");
	label->limitLabelWidth(labelMaxWidth, 1.f, 0.1f);
	label->setID(fmt::format("{}-label", nodeID));
	togglerMenu->addChild(label);

	togglerMenu->setContentWidth(
		toggler->getContentWidth() + gap + label->getScaledContentWidth()
	);
	togglerMenu->updateLayout();

	if (infoText) {
		auto infoBtn = CCMenuItemExt::createSpriteExtraWithFrameName(
			"GJ_infoIcon_001.png",
			0.6f,
			[infoText](CCMenuItemSpriteExtra*) {
				FLAlertLayer::create(
					"Info",
					infoText.value(),
					"OK"
				)->show();
			}
		);
		infoBtn->setID(fmt::format("{}-info-button", nodeID));
		infoBtn->setPosition(
			toggler->getPositionX() - toggler->getContentWidth() / 1.5f,
			toggler->getPositionY() + toggler->getContentHeight() / 1.5f
		);
		togglerMenu->addChild(infoBtn);
	}

	return togglerMenu;
}

std::optional<std::uint8_t> cbf::utils::validatePercentage(
	std::string const& percentageStr,
	std::optional<std::uint8_t> oldPercentage
) {
	if (percentageStr.empty()) {
		QuickNotification::create("Percentage can't be empty!", NotificationIcon::Error, 0.5f)->show();
		return std::nullopt;
	}

	auto percentageRes = numFromString<std::uint8_t>(percentageStr);
	if (!percentageRes) {
		QuickNotification::create("Failed to parse the number!", NotificationIcon::Error, 0.5f)->show();
		return std::nullopt;
	}

	auto percentage = percentageRes.unwrap();
	if (percentage > 100u) {
		QuickNotification::create("Percentage can't be above 100!", NotificationIcon::Error, 0.5f)->show();
		return std::nullopt;
	}

	do if (CBFToggleManager::get()->getDB()->contains(percentage)) {
		if (oldPercentage && percentage == oldPercentage.value())
			break;

		QuickNotification::create("Percentage already exists!", NotificationIcon::Error, 0.5f)->show();
		return std::nullopt;
	} while (false);

	return percentage;
}