#include <modules/gui/gui.hpp>
#include <modules/hack/hack.hpp>
#include <modules/config/config.hpp>

#include <Geode/modify/PlayerObject.hpp>

namespace eclipse::hacks::Player {

    class NoRobotFire : public hack::Hack {
        void init() override {
            auto tab = gui::MenuTab::find("Player");
            tab->addToggle("No Robot Fire", "player.norobotfire")
                ->setDescription("Disables the robot's fire when jumping.")
                ->handleKeybinds();
        }

        [[nodiscard]] const char* getId() const override { return "No Robot Fire"; }
    };

    REGISTER_HACK(NoRobotFire)

    class $modify(NoRobotFire_Hook, PlayerObject) {
        void update(float dt) override {
            if (!config::get<bool>("player.norobotfire", false))
                return PlayerObject::update(dt);

            PlayerObject::update(dt);
            m_robotFire->setVisible(false);
            m_robotBurstParticles->setVisible(false);
        }
    };

}
