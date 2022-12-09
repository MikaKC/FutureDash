#include "PlayerInfoLayer.hpp"

PlayerInfoLayer* PlayerInfoLayer::create()
{
    auto ptr = new (std::nothrow) PlayerInfoLayer;
    if(ptr && ptr->init(250, 150, "Quick info"))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return nullptr;
}

void PlayerInfoLayer::setup()
{
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    auto accountManager = gd::GJAccountManager::sharedState();
    auto gameStats = gd::GameStatsManager::sharedState();
    
    this->simplePlayerSprite = gd::SimplePlayer::create(gd::GameManager::sharedState()->getPlayerFrame());
    this->simplePlayerSprite->setPosition({m_pLrSize.width / 2 - 60, 0});
    this->simplePlayerSprite->setColor(gd::GameManager::sharedState()->colorForIdx(gd::GameManager::sharedState()->getPlayerColor()));
    this->simplePlayerSprite->setSecondColor(gd::GameManager::sharedState()->colorForIdx(gd::GameManager::sharedState()->getPlayerColor2()));
    this->simplePlayerSprite->setGlowOutline(gd::GameManager::sharedState()->getPlayerGlow());


    // auto simplePlayerBtn = gd::CCMenuItemSpriteExtra::create((CCSprite*)simplePlayerSprite, this, menu_selector(Callbacks::onPlayerIconPressed));
    
    auto playerBG = CCSprite::create("square02_001.png");
    playerBG->setPosition(this->simplePlayerSprite->getPosition());
    //playerBG->setPosition({-40, -40});
    //playerBG->setContentSize({simplePlayerSprite->getContentSize().width - 20, simplePlayerSprite->getContentSize().height - 20});
    playerBG->setScale(0.6f);
    playerBG->setOpacity(105);

    // Check player ID's (just for some like filler stuff)
    auto buttonSprite = gd::ButtonSprite::create("More info", 0, false, "bigFont.fnt", "GJ_button_01.png", 0, 0.5f);
    auto buttonSpriteBtn = gd::CCMenuItemSpriteExtra::create(buttonSprite, this, menu_selector(Callbacks::onMoreInfoPressed));
    buttonSpriteBtn->setPositionY(-m_pLrSize.height / 2 + 10);

    auto textArea = gd::TextArea::create("chatFont.fnt", false, std::string("<cg>Name</c>: " + accountManager->m_sUsername + "\n<cp>Stars</c>: " + std::to_string(gameStats->m_pPlayerStats->valueForKey("6")->intValue()) + "\n<cy>Gold</c> coins: " + std::to_string(gameStats->m_pPlayerStats->valueForKey("8")->intValue()) + "\n<cl>Silver</c> coins: " + std::to_string(gameStats->m_pPlayerStats->valueForKey("12")->intValue()) + "\n<cr>Demons</c>: " + std::to_string(gameStats->m_pPlayerStats->valueForKey("5")->intValue())), .75f, 100, 10, {0.5f, 0.5f});
    textArea->setPosition({-20, 0});

    // Need to make a new variable because
    auto leftArrowSpr = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    leftArrowSpr->setFlipX(true);

    auto leftArrow = gd::CCMenuItemSpriteExtra::create(leftArrowSpr, this, menu_selector(PlayerInfoLayer::onArrowLeftPressed));
    leftArrow->setScale(0.5f);
    leftArrow->m_fBaseScale = 0.5f;
    leftArrow->m_fScaleMultiplier = 1.25f;
    leftArrow->setPosition({30, 0});

    auto rightArrow = gd::CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("navArrowBtn_001.png"), this, menu_selector(PlayerInfoLayer::onArrowRightPressed));
    rightArrow->setScale(0.5f);
    rightArrow->m_fBaseScale = 0.5f;
    rightArrow->m_fScaleMultiplier = 1.25f;
    rightArrow->setPosition({100, 0});

    // Stuff
    m_pButtonMenu->addChild(simplePlayerSprite, 50);
    m_pButtonMenu->addChild(playerBG, 0);
    m_pButtonMenu->addChild(buttonSpriteBtn, 0);
    m_pButtonMenu->addChild(textArea, 5);
    m_pButtonMenu->addChild(leftArrow, 0);
    m_pButtonMenu->addChild(rightArrow, 0);
}

void PlayerInfoLayer::show()
{
    auto runningScene = CCDirector::sharedDirector()->getRunningScene();
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    runningScene->addChild(this);

    m_pLayer->setPosition({0 - m_pLrSize.width, 0});

    auto anim = CCMoveTo::create(0.5f, {0, 0});
    auto action = CCEaseElasticOut::create(anim, 0.6f);
    m_pLayer->runAction(action);
}

bool PlayerInfoLayer::init(float _w, float _h, std::string title)
{
    auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    m_pLrSize = cocos2d::CCSize { _w, _h };

    if (!this->initWithColor({ 0, 0, 0, 75 })) return false;
    this->m_pLayer = cocos2d::CCLayer::create();
    this->addChild(this->m_pLayer);

    auto bg = cocos2d::extension::CCScale9Sprite::create("GJ_square01.png", { 0.0f, 0.0f, 80.0f, 80.0f });
    bg->setContentSize(m_pLrSize);
    bg->setPosition(winSize.width / 2, winSize.height / 2);
    this->m_pLayer->addChild(bg);

    this->m_pButtonMenu = cocos2d::CCMenu::create();
    this->m_pLayer->addChild(this->m_pButtonMenu);

    this->setup();

    auto closeSpr = cocos2d::CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
    closeSpr->setScale(.8f);

    auto closeBtn = gd::CCMenuItemSpriteExtra::create(
        closeSpr,
        this,
        (cocos2d::SEL_MenuHandler)&PlayerInfoLayer::onClose
    );
    closeBtn->setUserData(reinterpret_cast<void*>(this));

    this->m_pButtonMenu->addChild(closeBtn);

    closeBtn->setPosition( - _w / 2, _h / 2 );

    this->setKeypadEnabled(true);
    this->setTouchEnabled(true);

    return true;
}


void PlayerInfoLayer::updateCheckIcon(CCObject* pSender)
{
    simplePlayerSprite->updatePlayerFrame(m_iCheckID, m_pCheckType);
}

void PlayerInfoLayer::animateAndChangeIcon(int id, float desiredScale, gd::IconType iconType)
{
    m_iCheckID = id;
    m_pCheckType = iconType;

    float transitionTime = 0.3f;

    simplePlayerSprite->runAction(
        CCSequence::create(
            CCEaseInOut::create(CCScaleTo::create(transitionTime, 0, 0), 2.f),
            CCCallFuncO::create(this, callfuncO_selector(PlayerInfoLayer::updateCheckIcon), this),
            CCEaseInOut::create(CCScaleTo::create(transitionTime, desiredScale, desiredScale), 2.f),
            nullptr
        )
    );
}

void PlayerInfoLayer::onArrowLeftPressed(cocos2d::CCObject* pSender)
{
    this->m_iCurrentIcon--;

    if(this->m_iCurrentIcon < 0) {
        this->m_iCurrentIcon = 6;
    }
    
    this->checkAndAnimate();
}

void PlayerInfoLayer::onArrowRightPressed(cocos2d::CCObject* pSender)
{
    this->m_iCurrentIcon++;

    if(this->m_iCurrentIcon > 6) {
        this->m_iCurrentIcon = 0;
    }

    this->checkAndAnimate();
}

// You can also kill me for this
void PlayerInfoLayer::checkAndAnimate()
{
    switch(this->m_iCurrentIcon)
    {
        case 0:
            this->animateAndChangeIcon(gd::GameManager::sharedState()->getPlayerFrame(), 1.f, gd::IconType::kIconTypeCube);
        break;
        case 1:
            this->animateAndChangeIcon(gd::GameManager::sharedState()->getPlayerShip(), 0.75f, gd::IconType::kIconTypeShip);
        break;
        case 2:
            this->animateAndChangeIcon(gd::GameManager::sharedState()->getPlayerBall(), 1.f, gd::IconType::kIconTypeBall);
        break;
        case 3:
            this->animateAndChangeIcon(gd::GameManager::sharedState()->getPlayerBird(), 1.f, gd::IconType::kIconTypeUfo);
        break;
        case 4:
            this->animateAndChangeIcon(gd::GameManager::sharedState()->getPlayerDart(), 1.f, gd::IconType::kIconTypeWave);
        break;
        case 5:
            this->animateAndChangeIcon(gd::GameManager::sharedState()->getPlayerRobot(), 1.f, gd::IconType::kIconTypeRobot);
        break;
        case 6:
            this->animateAndChangeIcon(gd::GameManager::sharedState()->getPlayerSpider(), 1.f, gd::IconType::kIconTypeSpider);
        break;
    }
}

void PlayerInfoLayer::onClose(cocos2d::CCObject *self)
{
    this->setKeyboardEnabled(false);
    this->removeFromParentAndCleanup(true);
}