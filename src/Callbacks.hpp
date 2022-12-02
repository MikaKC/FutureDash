#pragma once

#include "includes.h"
#include "InfoLayer.hpp"
#define ICON_TEXT(VAR, NAME, COLOUR) VAR = #NAME + std::string((COLOUR == "") ? "" : "</c>") + " ID: " + std::to_string(gd::GameManager::sharedState()->getPlayer##NAME())

class Callbacks {
protected:
    // IDK where to put this
    std::string iconStringFromName(gd::IconType type, std::string colour, bool addNewLine);
    

public:
    void onInfoButtonPressed(cocos2d::CCObject* pSender);
    void onMoreInfoPressed(cocos2d::CCObject* pSender);
};