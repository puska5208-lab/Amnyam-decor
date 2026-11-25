#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(AmnyamMenu, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto menu = this->getChildByID("bottom-menu");
        if (menu) {
            auto sprite = ButtonSprite::create("AMNYAM DECOR");
            auto button = CCMenuItemSpriteExtra::create(
                sprite, this, menu_selector(AmnyamMenu::onOpenDecor)
            );
            menu->addChild(button);
            menu->updateLayout();
        }

        return true;
    }

    void onOpenDecor(CCObject*) {
        createQuickPopup(
            "AMNYAM DECOR",
            "Выбери стиль украшения!",
            "Зелёный",
            "Жёлтый",
            [](auto, bool yellow) {
                if (yellow) {
                    FLAlertLayer::create(
                        "AMNYAM DECOR", "Выбран жёлтый декор!", "OK"
                    )->show();
                } else {
                    FLAlertLayer::create(
                        "AMNYAM DECOR", "Выбран зелёный декор!", "OK"
                    )->show();
                }
            }
        );
    }
};
