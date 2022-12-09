#pragma once

#include <Windows.h>
#include <gd.h>
#include <format>
#include <iostream>

// im pissed off over this shit
// #include "PlayerInfoLayer.hpp"
// #include "CreditsLayer.hpp"

class Callbacks
{
protected:
    inline std::string iconStringFromName(std::string const &icon, std::string const &colour, int const &id, bool const &addNewLine = true)
    {
        const std::string newLine = addNewLine ? "\n" : "";
        const std::string colourTag = colour == "" ? "" : std::format("<c{}>", colour);
        const std::string endColourTag = colour == "" ? "" : "</c>";
        const std::string iconText = newLine + colourTag + icon + endColourTag;
        
        return std::format("{} ID: {}", iconText, std::to_string(id));
    }
    
public:

    void onInfoButtonPressed(cocos2d::CCObject* pSender)
    {
        //PlayerInfoLayer::create()->show();
    }

    void onMoreInfoPressed(cocos2d::CCObject* pSender)
    {
        std::string playerCube = this->iconStringFromName("Cube", "r", gd::GameManager::sharedState()->getPlayerFrame(), false);
        std::string playerShip = this->iconStringFromName("Ship", "o", gd::GameManager::sharedState()->getPlayerShip());
        std::string playerBall = this->iconStringFromName("Ball", "y", gd::GameManager::sharedState()->getPlayerBall());
        std::string playerUFO = this->iconStringFromName("UFO", "g", gd::GameManager::sharedState()->getPlayerBird());
        std::string playerWave = this->iconStringFromName("Wave", "b", gd::GameManager::sharedState()->getPlayerDart());
        std::string playerRobot = this->iconStringFromName("Robot", "l", gd::GameManager::sharedState()->getPlayerRobot());
        std::string playerSpider = this->iconStringFromName("Spider", "p", gd::GameManager::sharedState()->getPlayerSpider());

        const std::string str = std::format("{}{}{}{}{}{}{}", playerCube, playerShip, playerBall, playerUFO, playerWave, playerRobot, playerSpider);
        
        ALERT("Icon info", "OK", nullptr, str);
    }

    void onMoreOptionsLayerButtonPressed(cocos2d::CCObject* pSender)
    {
        gd::MoreOptionsLayer::create()->show();
    }
    
    void onOptionsLayerButtonPressed(cocos2d::CCObject* pSender)
    {
        // IDK
        auto layer = gd::OptionsLayer::create();
        cocos2d::CCDirector::sharedDirector()->getRunningScene()->addChild(layer, 100);
        layer->showLayer(false);
    }

    void onCreditsButtonPressed(cocos2d::CCObject* pSender)
    {
        //CreditsLayer::create()->show();
    }

    void hidePauseLayerUI(cocos2d::CCNode* pSender)
    {
	   gd::PauseLayer* self = static_cast<gd::PauseLayer*>(pSender->getUserObject());
	   self->setVisible(false);
    }

    // Since hj's headers don't have this func, we add it ourselves
    gd::FLAlertLayer* createInfoLayer(gd::GJGameLevel* level)
	{
        return reinterpret_cast<gd::FLAlertLayer*(__fastcall*)(gd::GJGameLevel*, gd::GJUserScore*)>(
			gd::base + 0x14F4F0
        )(level, nullptr);
	}

    void onPauseLayerInfoPressed(cocos2d::CCObject* pSender)
    {
        createInfoLayer(gd::PlayLayer::get()->m_level)->show();
    }

    void onLevelBadgeInfo(cocos2d::CCObject* pSender)
    {
		switch(pSender->getTag())
		{
            // Info Badges
			case 1:
				ALERT("High Object Count", "OK", nullptr, "This level has more than <cr>40K</c> objects");
			break;
			case 2:
				ALERT("Collab", "OK", nullptr, "This level is a collab or has been copied");
			break;

            // Feature Badges
            case 3:
				ALERT("Featured", "OK", nullptr, "This level has been <cy>featured</c> by RobTop.");
			break;
            case 4:
				ALERT("Epic", "OK", nullptr, "This level has been <co>epic</c> featured by RobTop.");
			break;
		}
	}

    void onModeratorBadgeInfo(cocos2d::CCObject* pSender)
    {
		switch(pSender->getTag())
		{
            // Moderator Badges
			case 1:
				ALERT("Badge", "OK", nullptr, "This user is a <cy>Moderator</c>, they can send levels to RobTop.");
			break;
			case 2:
				ALERT("Badge", "OK", nullptr, "This user is an <cr>Elder Moderator</c>, they can send level to RobTop <cb>and</c> moderate chats.");
			break;
		}
	}
};