#include "Callbacks.hpp"

std::string Callbacks::iconStringFromName(gd::IconType type, std::string colour, bool addNewLine = true)
{

    std::string newLine = addNewLine ? "\n" : "";
    std::string iconString = std::string();

    // Will figure out how to change this
    switch (type)
    {
    case gd::IconType::kIconTypeCube:
        ICON_TEXT(iconString, Cube, colour);
        break;
    case gd::IconType::kIconTypeShip:
        ICON_TEXT(iconString, Ship, colour);
        break;
    case gd::IconType::kIconTypeBall:
        ICON_TEXT(iconString, Ball, colour);
        break;
    case gd::IconType::kIconTypeUfo:
        ICON_TEXT(iconString, UFO, colour);
        break;
    case gd::IconType::kIconTypeWave:
        ICON_TEXT(iconString, Wave, colour);
        break;
    case gd::IconType::kIconTypeRobot:
        ICON_TEXT(iconString, Robot, colour);
        break;
    case gd::IconType::kIconTypeSpider:
        ICON_TEXT(iconString, Spider, colour);
        break;
    }

    std::string colourTag = (colour == "") ? "" : "<c" + colour + ">";

    return newLine + colourTag + iconString;
}

void Callbacks::onInfoButtonPressed(cocos2d::CCObject* pSender)
{
    InfoLayer::create()->show();
}

void Callbacks::onMoreInfoPressed(cocos2d::CCObject* pSender)
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