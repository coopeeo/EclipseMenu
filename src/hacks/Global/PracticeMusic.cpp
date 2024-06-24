#include <modules/gui/gui.hpp>
#include <modules/hack/hack.hpp>
#include <modules/config/config.hpp>

#include <Geode/modify/GameStatsManager.hpp>

namespace eclipse::hacks::Global {

    class PracticeMusic : public hack::Hack {
        void init() override {
            auto tab = gui::MenuTab::find("Global");
            tab->addToggle("Practice Music Sync", "global.practicemusic");
        }

        [[nodiscard]] const char* getId() const override { return "Practice Music Sync"; }
    };

    REGISTER_HACK(PracticeMusic)

    class $modify(GameStatsManager) {
        static void onModify(auto& self) {
            SAFE_PRIORITY("GameStatsManager::isItemUnlocked");
        }

        bool isItemUnlocked(UnlockType type, int key) {
            if (GameStatsManager::isItemUnlocked(type, key))
                return true;

            if (config::get<bool>("global.practicemusic", false))
                return type == UnlockType::GJItem && key == 17;
            
            return false;
        }
    };
}