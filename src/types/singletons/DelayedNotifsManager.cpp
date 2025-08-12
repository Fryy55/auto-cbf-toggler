#include "DelayedNotifsManager.hpp"

using namespace geode::prelude;


DelayedNotifsManager* DelayedNotifsManager::get() {
	static auto instance = DelayedNotifsManager();
	
	return &instance;
}

void DelayedNotifsManager::add(Notification* notif) {
	notif->retain();
	m_queue.emplace_back(notif);

	return;
}

void DelayedNotifsManager::fire() {
	CCScheduler::get()->scheduleSelector(
		schedule_selector(DelayedNotifsManager::lateFire), this,
		0.f, 0, 0.f, false
	);

	return;
}

void DelayedNotifsManager::lateFire(float) {
	for (auto notif : m_queue) {
		notif->show();
		notif->release();
	}

	m_queue.clear();

	return;
}