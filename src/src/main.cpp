#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(AmnyamEditor, EditorUI) {
    struct Fields {
        CCTextInputNode* promptInput = nullptr;
    };

    bool init(LevelEditorLayer* editor) {
        if (!EditorUI::init(editor))
            return false;

        auto size = CCDirector::sharedDirector()->getWinSize();

        auto input = CCTextInputNode::create(
            220, 30,
            "Describe your decor...",
            "bigFont.fnt"
        );

        input->setPosition({size.width - 170, 150});
        this->addChild(input);
        m_fields->promptInput = input;

        auto button = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("CREATE"),
            this,
            menu_selector(AmnyamEditor::createDecor)
        );

        auto menu = CCMenu::create();
        menu->addChild(button);
        menu->setPosition({size.width - 35, 100});
        this->addChild(menu);

        return true;
    }

    void createDecor(CCObject*) {
        auto prompt = m_fields->promptInput->getString();

        if (prompt.empty()) {
            FLAlertLayer::create(
                "AMNYAM AI",
                "Describe your decor first!",
                "OK"
            )->show();
            return;
        }

        auto objects = this->getSelectedObjects();

        if (!objects || objects->count() == 0) {
            FLAlertLayer::create(
                "AMNYAM AI",
                "Select a building first!",
                "OK"
            )->show();
            return;
        }

        FLAlertLayer::create(
            "AMNYAM AI",
            "Your request has been received!\n"
            "Selected objects: " +
            std::to_string(objects->count()),
            "OK"
        )->show();
    }
};
