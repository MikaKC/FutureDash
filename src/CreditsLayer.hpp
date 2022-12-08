#pragma once

#include "includes.h"
#include "BrownAlertLayer.hpp"

class CreditsLayer : public BrownAlertLayer
{
protected:
    void onIconClicked(cocos2d::CCObject* pSender);

public:
    void setup() override;

    static CreditsLayer* create();
};