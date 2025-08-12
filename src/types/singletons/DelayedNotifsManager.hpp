#pragma once

#include <Geode/cocos/cocoa/CCObject.h>
#include <Geode/ui/Notification.hpp>


class DelayedNotifsManager final : public cocos2d::CCObject {
public:
	static DelayedNotifsManager* get();

private:
	DelayedNotifsManager() = default;

public:
	void add(geode::Notification* notif);
	void fire();

	DelayedNotifsManager(DelayedNotifsManager const&) = delete;
	DelayedNotifsManager(DelayedNotifsManager&&) = delete;
	DelayedNotifsManager& operator=(DelayedNotifsManager const&) = delete;
	DelayedNotifsManager& operator=(DelayedNotifsManager&&) = delete;

private:
	void lateFire(float);

	// Fields
	std::vector<geode::Notification*> m_queue{};
};