#pragma once

#include "includes.h"

// Extend from this class
class AlertLayerDelegate : public gd::FLAlertLayer
{
    protected:
        // layer size is stored here
        cocos2d::CCSize m_pLrSize;
        cocos2d::extension::CCScale9Sprite* m_pBGSprite;
        
        virtual bool init(float width, float height, const char* bg = "GJ_square01.png", const char* title = "")
        {
            auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
            this->m_pLrSize = cocos2d::CCSize { width, height };

            if (!this->initWithColor({ 0, 0, 0, 105 })) return false;
            this->m_pLayer = CCLayer::create();
            this->addChild(this->m_pLayer);

            auto _bg = cocos2d::extension::CCScale9Sprite::create(bg, { 0.0f, 0.0f, 80.0f, 80.0f });
            _bg->setContentSize(this->m_pLrSize);
            _bg->setPosition(winSize.width / 2, winSize.height / 2);
            this->m_pLayer->addChild(_bg);
            this->m_pBGSprite = _bg;

            this->m_pButtonMenu = cocos2d::CCMenu::create();
            this->m_pLayer->addChild(this->m_pButtonMenu);

            if (sizeof(title) > 0) {
                auto _title = cocos2d::CCLabelBMFont::create(title, "goldFont.fnt");

                _title->limitLabelWidth(this->m_pLrSize.width * 4, .75f, .2f);
                _title->setPosition(
                    winSize.width / 2,
                    winSize.height / 2 + this->m_pLrSize.height / 2 - 25
                );

                this->m_pLayer->addChild(_title);
            }

            setup();

            cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->incrementForcePrio(2);
            this->registerWithTouchDispatcher();
            
            auto closeSpr = cocos2d::CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
            closeSpr->setScale(1.0f);

            auto closeBtn = gd::CCMenuItemSpriteExtra::create(
                closeSpr,
                this,
                (cocos2d::SEL_MenuHandler)&AlertLayerDelegate::onClose
            );
            closeBtn->setUserData(reinterpret_cast<void*>(this));

            this->m_pButtonMenu->addChild(closeBtn);

            closeBtn->setPosition(-width / 2 + 10, height / 2 - 10);

            this->setKeypadEnabled(true);
            this->setTouchEnabled(true);

            return true;
        }

        virtual void setup() = 0;

        virtual void keyDown(cocos2d::enumKeyCodes key) override
        {
            if (key == cocos2d::KEY_Escape)
                return onClose(nullptr);
            if (key == cocos2d::KEY_Space)
                return;
            
            return FLAlertLayer::keyDown(key);
        }

        virtual void onClose(cocos2d::CCObject* pSender)
        {
            this->setKeyboardEnabled(false);
            this->removeFromParentAndCleanup(true);
        }
};