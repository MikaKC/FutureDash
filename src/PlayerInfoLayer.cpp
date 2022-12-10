#include "PlayerInfoLayer.hpp"

PlayerInfoLayer* PlayerInfoLayer::create(MenuLayerHook* menulayer)
{
	auto ptr = new (std::nothrow) PlayerInfoLayer;
	if(ptr && ptr->init(250, 150, "Quick info", menulayer))
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

	auto accountManager = GJAccountManager::sharedState();
	auto gameStats = GameStatsManager::sharedState();
	
	this->simplePlayerSprite = SimplePlayer::create(0);
	this->simplePlayerSprite->updatePlayerFrame(m_iCheckID, m_pCheckType);
	this->simplePlayerSprite->setPosition({m_pLrSize.width / 2 - 60, 0});
	this->simplePlayerSprite->setColor(GM->colorForIdx(GM->getPlayerColor()));
	this->simplePlayerSprite->setSecondColor(GM->colorForIdx(GM->getPlayerColor2()));
	this->simplePlayerSprite->setGlowOutline(GM->getPlayerGlow());


	// auto simplePlayerBtn = CCMenuItemSpriteExtra::create((CCSprite*)simplePlayerSprite, this, menu_selector(Callbacks::onPlayerIconPressed));
	
	auto playerBG = CCSprite::create("square02_001.png");
	playerBG->setPosition(this->simplePlayerSprite->getPosition());
	//playerBG->setPosition({-40, -40});
	//playerBG->setContentSize({simplePlayerSprite->getContentSize().width - 20, simplePlayerSprite->getContentSize().height - 20});
	playerBG->setScale(0.6f);
	playerBG->setOpacity(105);

	// Check player ID's (just for some like filler stuff)
	auto buttonSprite = ButtonSprite::create("More info", 0, false, "bigFont.fnt", "GJ_button_01.png", 0, 0.5f);
	auto buttonSpriteBtn = CCMenuItemSpriteExtra::create(buttonSprite, this, menu_selector(PlayerInfoLayer::onMoreInfoPressed));
	buttonSpriteBtn->setPositionY(-m_pLrSize.height / 2 + 10);

	auto textArea = TextArea::create("chatFont.fnt", false, std::string("<cg>Name</c>: " + accountManager->m_sUsername + "\n<cp>Stars</c>: " + std::to_string(gameStats->m_pPlayerStats->valueForKey("6")->intValue()) + "\n<cy>Gold</c> coins: " + std::to_string(gameStats->m_pPlayerStats->valueForKey("8")->intValue()) + "\n<cl>Silver</c> coins: " + std::to_string(gameStats->m_pPlayerStats->valueForKey("12")->intValue()) + "\n<cr>Demons</c>: " + std::to_string(gameStats->m_pPlayerStats->valueForKey("5")->intValue())), .75f, 100, 10, {0.5f, 0.5f});
	textArea->setPosition({-20, 0});

	// Need to make a new variable because
	auto leftArrowSpr = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
	leftArrowSpr->setFlipX(true);

	auto leftArrow = CCMenuItemSpriteExtra::create(leftArrowSpr, this, menu_selector(PlayerInfoLayer::onNextIcon));
	leftArrow->setTag(-1);
	leftArrow->setScale(0.5f);
	leftArrow->m_fBaseScale = 0.5f;
	leftArrow->m_fScaleMultiplier = 1.25f;
	leftArrow->setPosition({30, 0});

	auto rightArrow = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("navArrowBtn_001.png"), this, menu_selector(PlayerInfoLayer::onNextIcon));
	rightArrow->setTag(1);
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

void PlayerInfoLayer::onMoreInfoPressed(cocos2d::CCObject* pSender)
{
	std::string playerCube = this->iconStringFromName("Cube", "r", GM->getPlayerFrame(), false);
	std::string playerShip = this->iconStringFromName("Ship", "o", GM->getPlayerShip());
	std::string playerBall = this->iconStringFromName("Ball", "y", GM->getPlayerBall());
	std::string playerUFO = this->iconStringFromName("UFO", "g", GM->getPlayerBird());
	std::string playerWave = this->iconStringFromName("Wave", "b", GM->getPlayerDart());
	std::string playerRobot = this->iconStringFromName("Robot", "l", GM->getPlayerRobot());
	std::string playerSpider = this->iconStringFromName("Spider", "p", GM->getPlayerSpider());

	const std::string str = std::format("{}{}{}{}{}{}{}", playerCube, playerShip, playerBall, playerUFO, playerWave, playerRobot, playerSpider);
	
	ALERT("Icon info", "OK", nullptr, str);
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

bool PlayerInfoLayer::init(float _w, float _h, std::string title, MenuLayerHook* menulayer)
{
	m_pLrSize = cocos2d::CCSize { _w, _h };
	this->m_pMenuLayer = menulayer;

	if (!this->initWithColor({ 0, 0, 0, 75 })) return false;
	this->m_pLayer = cocos2d::CCLayer::create();
	this->addChild(this->m_pLayer);

	auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
	auto bg = cocos2d::extension::CCScale9Sprite::create("GJ_square01.png", { 0.0f, 0.0f, 80.0f, 80.0f });
	bg->setContentSize(m_pLrSize);
	bg->setPosition(winSize.width / 2, winSize.height / 2);
	this->m_pLayer->addChild(bg);

	this->m_pButtonMenu = cocos2d::CCMenu::create();
	this->m_pLayer->addChild(this->m_pButtonMenu);
	
	
	this->m_iCurrentIcon = static_cast<int>(GM->getPlayerIconType());
	this->m_pCheckType = GM->getPlayerIconType();
	this->m_iCheckID = ModToolbox::frameForIcon(GM->getPlayerIconType());

	if (sizeof(title) > 0) {
		auto labelTitle = CCLabelBMFont::create(title.c_str(), "goldFont.fnt");

		labelTitle->limitLabelWidth(this->m_pLrSize.width * 4, .75f, .2f);
		labelTitle->setPosition(
			winSize.width / 2,
			winSize.height / 2 + this->m_pLrSize.height / 2 - 25
		);

		this->m_pLayer->addChild(labelTitle);
    }

	this->setup();

	auto closeSpr = cocos2d::CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
	closeSpr->setScale(.8f);

	auto closeBtn = CCMenuItemSpriteExtra::create(
	closeSpr,
	this,
	(cocos2d::SEL_MenuHandler)&PlayerInfoLayer::onClose
	);
	closeBtn->setUserData(reinterpret_cast<void*>(this));

	this->m_pButtonMenu->addChild(closeBtn);

	closeBtn->setPosition( - _w / 2 + 10, _h / 2 - 10);

	this->setKeypadEnabled(true);
	this->setTouchEnabled(true);

	return true;
}


void PlayerInfoLayer::updateCheckIcon(CCObject* pSender)
{
	simplePlayerSprite->updatePlayerFrame(m_iCheckID, m_pCheckType);
}

void PlayerInfoLayer::animateAndChangeIcon(int id, float desiredScale, IconType iconType)
{
	m_iCheckID = id;
	m_pCheckType = iconType;
	GM->setPlayerIconType(m_pCheckType);

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

void PlayerInfoLayer::onNextIcon(cocos2d::CCObject* pSender)
{
	if(pSender->getTag() > 0)
		m_iCurrentIcon = m_iCurrentIcon >= 6 ? 0 : m_iCurrentIcon + 1; //right
	else
		m_iCurrentIcon = m_iCurrentIcon <= 0 ? 6 : m_iCurrentIcon - 1; //left
	
	this->checkAndAnimate();
}

// here u go 👍
void PlayerInfoLayer::checkAndAnimate()
{
	float scale = this->m_iCurrentIcon == 1 ? 0.75f : 1.f;
	auto icon = static_cast<IconType>(this->m_iCurrentIcon);
	
	this->animateAndChangeIcon(ModToolbox::frameForIcon(icon), scale, icon);
}

void PlayerInfoLayer::onClose(cocos2d::CCObject *self)
{
	this->setKeyboardEnabled(false);
	this->removeFromParentAndCleanup(true);
	this->m_pMenuLayer->m_pProfileIconSprite->updatePlayerFrame(m_iCheckID, m_pCheckType);
}


std::string PlayerInfoLayer::iconStringFromName(std::string const &icon, std::string const &colour, int const &id, bool const &addNewLine)
{
	const std::string newLine = addNewLine ? "\n" : "";
	const std::string colourTag = colour == "" ? "" : std::format("<c{}>", colour);
	const std::string endColourTag = colour == "" ? "" : "</c>";
	const std::string iconText = newLine + colourTag + icon + endColourTag;
	
	return std::format("{} ID: {}", iconText, std::to_string(id));
}


