#pragma once

#include "includes.h"

class PlayerInfoLayer : public gd::FLAlertLayer
{
protected:
    int m_iCurrentIcon = 0;
    gd::SimplePlayer* simplePlayerSprite;

    int m_iCheckID = 0;
    gd::IconType m_pCheckType = gd::IconType::kIconTypeCube;
    CCSize m_pLrSize;

public:
    bool init(float _w, float _h, std::string title);
    void show() override;
    void setup();

    void onArrowLeftPressed(cocos2d::CCObject* pSender);
    void onArrowRightPressed(cocos2d::CCObject* pSender);
    void updateCheckIcon(cocos2d::CCObject* pSender);
    void onClose(cocos2d::CCObject* pSender);
    
    void checkAndAnimate();
    void animateAndChangeIcon(int id, float desiredScale, gd::IconType iconType);

    static PlayerInfoLayer* create();
};