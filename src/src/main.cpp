#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(AmnyamMenu, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto menu = this->getChildByID("bottom-menu");
        if (menu) {
            auto btn = CCMenuItemSpriteExtra::create(
                ButtonSprite::create("AMNYAM DECOR"),
                this,
                menu_selector(AmnyamMenu::openDecor)
            );
            menu->addChild(btn);
            menu->updateLayout();
        }
        return true;
    }

    void openDecor(CCObject*) {
        createQuickPopup(
            "AMNYAM DECOR",
            "Choose your decoration style!",
            "Green",
            "Yellow",
            [](auto, bool yellow) {
                FLAlertLayer::create(
                    "AMNYAM DECOR",
                    yellow ? "Yellow Decor selected!" : "Green Decor selected!",
                    "OK"
                )->show();
            }
        );
    }
};
