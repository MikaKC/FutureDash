#pragma once

#include "includes.h"
#include "BrownAlertLayer.hpp"

class InfoLayer : public BrownAlertLayer
{
protected:
    int m_iCurrentIcon = 0;
    gd::SimplePlayer* simplePlayerSprite;

    int m_iCheckID = 0;
    gd::IconType m_pCheckType = gd::IconType::kIconTypeCube;

public:
    void setup() override;
    void show() override;

    void onArrowLeftPressed(cocos2d::CCObject* pSender);
    void onArrowRightPressed(cocos2d::CCObject* pSender);
    void updateCheckIcon(cocos2d::CCObject* pSender);
    
    void checkAndAnimate();
    void animateAndChangeIcon(int id, float desiredScale, gd::IconType iconType);

    static InfoLayer* create();
};