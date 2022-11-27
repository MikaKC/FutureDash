#include "Callbacks.hpp"

void Callbacks::onInfoButtonPressed(cocos2d::CCObject* pSender)
{
    InfoLayer::create()->show();
}

void Callbacks::onMoreInfoPressed(cocos2d::CCObject* pSender)
{
    // You can come and kill me iyw
    std::string playerCube = "<cr>Cube</c> ID: " + std::to_string(gd::GameManager::sharedState()->getPlayerFrame());
    std::string playerShip = "\n<co>Ship</c> ID: " + std::to_string(gd::GameManager::sharedState()->getPlayerShip());
    std::string playerBall = "\n<cy>Ball</c> ID: " + std::to_string(gd::GameManager::sharedState()->getPlayerBall());
    std::string playerUFO = "\n<cg>UFO</c> ID: " + std::to_string(gd::GameManager::sharedState()->getPlayerBird());
    std::string playerWave = "\n<cb>Wave</c> ID: " + std::to_string(gd::GameManager::sharedState()->getPlayerDart());
    std::string playerRobot = "\n<cp>Robot</c> ID: " + std::to_string(gd::GameManager::sharedState()->getPlayerRobot());
    std::string playerSpider = "\n<cr>Spider</c> ID: " + std::to_string(gd::GameManager::sharedState()->getPlayerSpider());

    ALERT("Icon info", "Ok", nullptr, std::string(playerCube + playerShip + playerBall + playerUFO + playerWave + playerRobot + playerSpider));
}