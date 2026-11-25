
#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(AmnyamEditor, EditorUI) {
    bool init(LevelEditorLayer* editor) {
        if (!EditorUI::init(editor)) return false;

        auto btn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("DEC"),
            this,
            menu_selector(AmnyamEditor::openDecor)
        );

        auto menu = CCMenu::create();
        menu->addChild(btn);

        auto size = CCDirector::sharedDirector()->getWinSize();
        menu->setPosition({size.width - 35, 150});

        this->addChild(menu);
        return true;
    }

    void openDecor(CCObject*) {
        createQuickPopup(
            "AMNYAM DECOR",
            "Choose decoration color!",
            "Green",
            "More colors",
            [this](auto, bool more) {
                if (more) {
                    createQuickPopup(
                        "AMNYAM DECOR",
                        "Choose another color!",
                        "Blue",
                        "Yellow",
                        [](auto, bool yellow) {
                            FLAlertLayer::create(
                                "AMNYAM DECOR",
                                yellow ? "Yellow selected!" : "Blue selected!",
                                "OK"
                            )->show();
                        }
                    );
                } else {
                    FLAlertLayer::create(
                        "AMNYAM DECOR",
                        "Green selected!",
                        "OK"
                    )->show();
                }
            }
        );
    }
};
