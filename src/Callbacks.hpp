#pragma once
#include "includes.h"
#include "InfoLayer.hpp"

class Callbacks 
{
protected:
    inline std::string iconStringFromName(gd::IconType const& type, std::string const& colour, bool const& addNewLine = true)
    {

        const std::string newLine = addNewLine ? "\n" : "";
        std::string iconString = std::string();

        // Will figure out how to change this
        switch (type)
        {
        case gd::IconType::kIconTypeCube:
            iconString = "Cube" + std::string((colour == "") ? "" : "</c>") + " ID: " + std::to_string(gd::GameManager::sharedState()->getPlayerFrame());
            break;
        case gd::IconType::kIconTypeShip:
            iconString = "Ship" + std::string((colour == "") ? "" : "</c>") + " ID: " + std::to_string(gd::GameManager::sharedState()->getPlayerShip());
            break;
        case gd::IconType::kIconTypeBall:
            iconString = "Ball" + std::string((colour == "") ? "" : "</c>") + " ID: " + std::to_string(gd::GameManager::sharedState()->getPlayerBall());
            break;
        case gd::IconType::kIconTypeUfo:
            iconString = "UFO" + std::string((colour == "") ? "" : "</c>") + " ID: " + std::to_string(gd::GameManager::sharedState()->getPlayerBird());
            break;
        case gd::IconType::kIconTypeWave:
            iconString = "Wave" + std::string((colour == "") ? "" : "</c>") + " ID: " + std::to_string(gd::GameManager::sharedState()->getPlayerDart());
            break;
        case gd::IconType::kIconTypeRobot:
            iconString = "Robot" + std::string((colour == "") ? "" : "</c>") + " ID: " + std::to_string(gd::GameManager::sharedState()->getPlayerRobot());
            break;
        case gd::IconType::kIconTypeSpider:
            iconString = "Spider" + std::string((colour == "") ? "" : "</c>") + " ID: " + std::to_string(gd::GameManager::sharedState()->getPlayerSpider());
            break;
        }

        const std::string colourTag = (colour == "") ? "" : "<c" + colour + ">";

        return newLine + colourTag + iconString;
    }
    
public:
    void onInfoButtonPressed(cocos2d::CCObject* pSender)
    {
        auto* layer = InfoLayer::create();
        layer->show();
    }

    void onMoreInfoPressed(cocos2d::CCObject* pSender)
    {
        std::string playerCube = this->iconStringFromName(gd::IconType::kIconTypeCube, "r", false);
        std::string playerShip = this->iconStringFromName(gd::IconType::kIconTypeShip, "o");
        std::string playerBall = this->iconStringFromName(gd::IconType::kIconTypeBall, "y");
        std::string playerUFO = this->iconStringFromName(gd::IconType::kIconTypeUfo, "g");
        std::string playerWave = this->iconStringFromName(gd::IconType::kIconTypeWave, "b");
        std::string playerRobot = this->iconStringFromName(gd::IconType::kIconTypeRobot, "l");
        std::string playerSpider = this->iconStringFromName(gd::IconType::kIconTypeSpider, "p");

        std::string allTexts(playerCube + playerShip + playerBall + playerUFO + playerWave + playerRobot + playerSpider);
        
        ALERT("Icon info", "Ok", nullptr, allTexts);
    }

    void onMoreOptionsLayerButtonPressed(cocos2d::CCObject* pSender)
    {
        gd::MoreOptionsLayer::create()->show();
    }
    
    void onOptionsLayerButtonPressed(cocos2d::CCObject* pSender)
    {
        // IDK
        auto rs = cocos2d::CCDirector::sharedDirector()->getRunningScene();
        auto lr = gd::OptionsLayer::create();
        rs->addChild(lr, 100);
        lr->showLayer(false);
    }
};