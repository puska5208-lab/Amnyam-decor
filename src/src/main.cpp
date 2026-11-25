
#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(AmnyamEditor, EditorUI) {

    bool init(LevelEditorLayer* editor) {
        if (!EditorUI::init(editor))
            return false;

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
        auto objects = this->getSelectedObjects();

        int count = objects ? objects->count() : 0;

        FLAlertLayer::create(
            "AMNYAM DECOR",
            fmt::format(
                "Selected objects: {}",
                count
            ),
            "OK"
        )->show();
    }
};
