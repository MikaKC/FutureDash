#include "Callbacks.hpp"

void Callbacks::onInfoButtonPressed(cocos2d::CCObject* pSender)
{
    InfoLayer::create()->show();
}

void Callbacks::onMoreInfoPressed(cocos2d::CCObject* pSender)
{
    // You can come and kill me iyw
    std::string playerCube = "Cube ID: " + std::_Integral_to_string<char>(gd::GameManager::sharedState()->getPlayerFrame());
    std::string playerShip = "\nShip ID: " + std::_Integral_to_string<char>(gd::GameManager::sharedState()->getPlayerShip());
    std::string playerBall = "\nBall ID: " + std::_Integral_to_string<char>(gd::GameManager::sharedState()->getPlayerBall());
    std::string playerUFO = "\nUFO ID: " + std::_Integral_to_string<char>(gd::GameManager::sharedState()->getPlayerBird());
    std::string playerWave = "\nWave ID: " + std::_Integral_to_string<char>(gd::GameManager::sharedState()->getPlayerDart());
    std::string playerRobot = "\nRobot ID: " + std::_Integral_to_string<char>(gd::GameManager::sharedState()->getPlayerRobot());
    std::string playerSpider = "\nSpider ID: " + std::_Integral_to_string<char>(gd::GameManager::sharedState()->getPlayerSpider());

    ALERT("Icon info", "Ok", nullptr, std::string(playerCube + playerShip + playerBall + playerUFO + playerWave + playerRobot + playerSpider));
}