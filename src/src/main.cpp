#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <chrono>
#include <deque>

using namespace geode::prelude;

static std::deque<std::chrono::steady_clock::time_point> requests;

class $modify(AmnyamEditor, EditorUI) {

    struct Fields {
        CCTextInputNode* promptInput = nullptr;
    };

    bool init(LevelEditorLayer* editor) {
        if (!EditorUI::init(editor))
            return false;

        auto size = CCDirector::sharedDirector()->getWinSize();

        auto input = CCTextInputNode::create(
            220,
            30,
            "Describe your decor...",
            "bigFont.fnt"
        );

        input->setPosition({size.width - 170, 150});
        this->addChild(input);
        m_fields->promptInput = input;

        auto btn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("CREATE"),
            this,
            menu_selector(AmnyamEditor::openDecor)
        );

        auto menu = CCMenu::create();
        menu->addChild(btn);
        menu->setPosition({size.width - 35, 150});
        this->addChild(menu);

        return true;
    }

    void openDecor(CCObject*) {
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
        int count = objects ? objects->count() : 0;

        if (count == 0) {
            FLAlertLayer::create(
                "AMNYAM AI",
                "Select a building first!",
                "OK"
            )->show();
            return;
        }

        auto now = std::chrono::steady_clock::now();
        auto limit = std::chrono::minutes(10);

        while (!requests.empty() &&
               now - requests.front() >= limit) {
            requests.pop_front();
        }

        if (requests.size() >= 100) {
            auto remaining =
                std::chrono::duration_cast<std::chrono::seconds>(
                    limit - (now - requests.front())
                ).count();

            FLAlertLayer::create(
                "AMNYAM AI",
                fmt::format(
                    "Request limit reached! Try again in {} min. {} sec.",
                    remaining / 60,
                    remaining % 60
                ),
                "OK"
            )->show();

            return;
        }

        requests.push_back(now);

        FLAlertLayer::create(
            "AMNYAM AI",
            fmt::format(
                "Your prompt: {}\nSelected objects: {}\n\nAI integration is coming in the next update!",
                prompt,
                count
            ),
            "OK"
        )->show();
    }
};
