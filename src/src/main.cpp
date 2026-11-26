#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <fmt/format.h>

using namespace geode::prelude;

class $modify(AmnyamEditor, EditorUI) {
    struct Fields {
        CCMenu* colorMenu = nullptr;
        int red = 0;
        int green = 255;
        int blue = 0;
    };

    bool init(LevelEditorLayer* editor) {
        if (!EditorUI::init(editor))
            return false;

        auto size = CCDirector::sharedDirector()->getWinSize();

        auto menu = CCMenu::create();

        auto decButton = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("DEC"),
            this,
            menu_selector(AmnyamEditor::toggleColors)
        );

        menu->addChild(decButton);
        menu->setPosition({size.width - 65, 100});
        this->addChild(menu);

        auto colors = CCMenu::create();

        auto yellow = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("YELLOW"),
            this,
            menu_selector(AmnyamEditor::chooseYellow)
        );

        auto blue = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("BLUE"),
            this,
            menu_selector(AmnyamEditor::chooseBlue)
        );

        auto green = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("GREEN"),
            this,
            menu_selector(AmnyamEditor::chooseGreen)
        );

        yellow->setPosition({-100, 0});
        blue->setPosition({0, 0});
        green->setPosition({100, 0});

        colors->addChild(yellow);
        colors->addChild(blue);
        colors->addChild(green);

        colors->setPosition({size.width - 165, 55});
        colors->setVisible(false);

        this->addChild(colors);
        m_fields->colorMenu = colors;

        return true;
    }

    void toggleColors(CCObject*) {
        auto menu = m_fields->colorMenu;
        menu->setVisible(!menu->isVisible());
    }

    void chooseYellow(CCObject*) {
        m_fields->red = 255;
        m_fields->green = 220;
        m_fields->blue = 30;
        createDecor();
    }

    void chooseBlue(CCObject*) {
        m_fields->red = 30;
        m_fields->green = 120;
        m_fields->blue = 255;
        createDecor();
    }

    void chooseGreen(CCObject*) {
        m_fields->red = 30;
        m_fields->green = 255;
        m_fields->blue = 70;
        createDecor();
    }

    void createDecor() {
        auto objects = this->getSelectedObjects();

        if (!objects || objects->count() == 0) {
            FLAlertLayer::create(
                "DEC",
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

            auto addDecor = [&](float x, float y) {
                auto data = fmt::format(
                    "1,1,2,{:.2f},3,{:.2f},32,{:.3f},7,{:.0f},8,{:.0f},9,{:.0f}",
                    x,
                    y,
                    decoScale,
                    static_cast<float>(m_fields->red),
                    static_cast<float>(m_fields->green),
                    static_cast<float>(m_fields->blue)
                );

                m_editorLayer->createObjectsFromString(
                    data, false, false
                );

                added++;
            };

            addDecor(pos.x - offset, pos.y);
            addDecor(pos.x + offset, pos.y);
            addDecor(pos.x, pos.y + offset);
            addDecor(pos.x, pos.y - offset);
            addDecor(pos.x - offset, pos.y + offset);
            addDecor(pos.x + offset, pos.y + offset);
            addDecor(pos.x - offset, pos.y - offset);
            addDecor(pos.x + offset, pos.y - offset);
        }

        m_fields->colorMenu->setVisible(false);

        FLAlertLayer::create(
            "AMNYAM DEC",
            fmt::format("Added {} decor objects!", added),
            "NICE!"
        )->show();
    }
};
