#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <fmt/format.h>

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
                "Select blocks first!",
                "OK"
            )->show();
            return;
        }

        int added = 0;

        for (int i = 0; i < objects->count(); i++) {
            auto obj = static_cast<GameObject*>(
                objects->objectAtIndex(i)
            );

            if (!obj)
                continue;

            auto pos = obj->getPosition();
            float scale = obj->getScale();

            if (scale <= 0.f)
                scale = 1.f;

            float offset = 5.f * scale;
            float decoScale = 0.18f * scale;

            auto addInside = [&](float x, float y) {
                auto data = fmt::format(
                    "1,1,2,{:.2f},3,{:.2f},32,{:.3f}",
                    x, y, decoScale
                );

                m_editorLayer->createObjectsFromString(
                    data, false, false
                );

                added++;
            };

            addInside(pos.x - offset, pos.y);
            addInside(pos.x + offset, pos.y);
            addInside(pos.x, pos.y + offset);
            addInside(pos.x, pos.y - offset);
        }

        FLAlertLayer::create(
            "AMNYAM AI",
            fmt::format("Added {} decor objects!", added),
            "OK"
        )->show();
    }
};
