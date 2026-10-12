#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyVisualsMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // 1. Добавление кнопки "Визуалы" возле кнопки Geode
        if (auto geodeBtn = this->getChildByID("geode.loader/geode-button")) {
            auto menu = geodeBtn->getParent();

            auto btnSprite = CircleButtonSprite::createWithSpriteFrameName(
                "GJ_paintBtn_001.png",
                1.0f,
                CircleBaseColor::Green,
                CircleBaseSize::Medium
            );

            auto visualBtn = CCMenuItemSpriteExtra::create(
                btnSprite,
                this,
                menu_selector(MyVisualsMenuLayer::onVisualsClicked)
            );

            visualBtn->setPosition(geodeBtn->getPosition() + ccp(45.0f, 0.0f));
            visualBtn->setID("visual-customizer-button"_spr);
            menu->addChild(visualBtn);
        }

        // 2. Установка собственного фона
        auto bgPath = Mod::get()->getSettingValue<std::filesystem::path>("custom-background");
        if (!bgPath.empty() && std::filesystem::exists(bgPath)) {
            if (auto mainBG = this->getChildByID("main-title-bg")) {
                auto texture = CCTextureCache::sharedTextureCache()->addImage(bgPath.string().c_str(), false);
                if (texture) {
                    auto sprite = static_cast<CCSprite*>(mainBG);
                    sprite->setTexture(texture);
                    sprite->setTextureRect({0, 0, texture->getContentSize().width, texture->getContentSize().height});
                }
            }
        }

        // 3. Установка собственной музыки
        auto musicPath = Mod::get()->getSettingValue<std::filesystem::path>("custom-music");
        if (!musicPath.empty() && std::filesystem::exists(musicPath)) {
            GameMusicManager::sharedState()->playMenuMusic(musicPath.string());
        }

        return true;
    }

    void onVisualsClicked(CCObject* sender) {
        geode::openSettingsPopup(Mod::get());
    }
};

// --- Применение разрешения 4:3 ---
$execute {
    if (Mod::get()->getSettingValue<bool>("stretch-4-3")) {
        auto director = CCDirector::sharedDirector();
        auto winSize = director->getWinSize();
        
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(
            winSize.height * (4.0f / 3.0f),
            winSize.height,
            kResolutionExactFit
        );
    }
}
