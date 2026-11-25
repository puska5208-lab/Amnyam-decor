#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <algorithm>

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

        float minX = 999999.f;
        float minY = 999999.f;
        float maxX = -999999.f;
        float maxY = -999999.f;

        for (int i = 0; i < objects->count(); i++) {
            auto obj = static_cast<GameObject*>(
                objects->objectAtIndex(i)
            );

            auto pos = obj->getPosition();

            minX = std::min(minX, pos.x);
            minY = std::min(minY, pos.y);
            maxX = std::max(maxX, pos.x);
            maxY = std::max(maxY, pos.y);
        }

        float centerX = (minX + maxX) / 2.f;
        float centerY = (minY + maxY) / 2.f;

        float offset = 25.f;

        auto addDecor = [&](float x, float y) {
            auto data = fmt::format(
                "1,1,2,{:.2f},3,{:.2f},32,0.35",
                x, y
            );

            m_editorLayer->addObjectFromString(data);
        };

        addDecor(minX - offset, maxY + offset);
        addDecor(centerX, maxY + offset);
        addDecor(maxX + offset, maxY + offset);

        addDecor(minX - offset, centerY);
        addDecor(maxX + offset, centerY);

        addDecor(minX - offset, minY - offset);
        addDecor(centerX, minY - offset);
        addDecor(maxX + offset, minY - offset);

        FLAlertLayer::create(
            "AMNYAM AI",
            "Decor objects added!",
            "OK"
        )->show();
    }
};
