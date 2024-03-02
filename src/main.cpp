#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>

using namespace geode::prelude;

$execute {
	using namespace keybinds;

	BindManager::get()->registerBindable({
		"restart"_spr,
		"Endscreen Restart",
		"Restarts the level at the endscreen.",
		{Keybind::create(KEY_R, Modifier::None)}
	});
}

class $modify(PlayLayer) {
	bool init(GJGameLevel* level, bool p1, bool p2) {
		if (!PlayLayer::init(level, p1, p2)) return false;

		this->template addEventListener<keybinds::InvokeBindFilter>([=](keybinds::InvokeBindEvent* event) {
			auto endLevelLayer = static_cast<EndLevelLayer*>(PlayLayer::getChildByID("EndLevelLayer"));

			if (event->isDown() && endLevelLayer != nullptr) {
				endLevelLayer->onReplay(this);
			}

			return ListenerResult::Stop;
		}, "restart"_spr);

		return true;
	}
};