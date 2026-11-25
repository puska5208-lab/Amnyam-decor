#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(AmnyamEditor, EditorUI) {
    bool init(LevelEditorLayer* editor) {
        if (!EditorUI::init(editor)) return false;

        auto btn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("AMNYAM DECOR"),
            this,
            menu_selector(AmnyamEditor::openDecor)
        );

        auto menu = CCMenu::create();
        menu->addChild(btn);
        menu->setPosition({ 100, 60 });
        this->addChild(menu);

        return true;
    }

    void openDecor(CCObject*) {
        createQuickPopup(
            "AMNYAM DECOR",
            "Choose decoration style!",
            "Green",
            "Yellow",
            [](auto, bool yellow) {
                FLAlertLayer::create(
                    "AMNYAM DECOR",
                    yellow ? "Yellow selected!" : "Green selected!",
                    "OK"
                )->show();
            }
        );
    }
};
