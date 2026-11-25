
#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(AmnyamEditor, EditorUI) {

    bool init(LevelEditorLayer* editor) {
        if (!EditorUI::init(editor))
            return false;

        auto btn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("AI"),
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

        if (count == 0) {
            FLAlertLayer::create(
                "AMNYAM AI",
                "Select a building first!",
                "OK"
            )->show();
            return;
        }

        createQuickPopup(
            "AMNYAM AI",
            fmt::format(
                "Selected objects: {}\nChoose a color:",
                count
            ),
            "Yellow",
            "More colors",
            [this](auto, bool btn2) {
                if (!btn2) {
                    showColor("Yellow");
                } else {
                    createQuickPopup(
                        "AMNYAM AI",
                        "Choose a color:",
                        "Blue",
                        "Green",
                        [this](auto, bool green) {
                            showColor(green ? "Green" : "Blue");
                        }
                    );
                }
            }
        );
    }

    void showColor(std::string color) {
        FLAlertLayer::create(
            "AMNYAM AI",
            fmt::format(
                "Selected color: {}\nAI editing will be connected next!",
                color
            ),
            "OK"
        )->show();
    }
};
