#include "SelectMoreOptionsLayer.h"

SelectMoreOptionsLayer* SelectMoreOptionsLayer::create()
{
	auto pRet = new (std::nothrow) SelectMoreOptionsLayer;
	
	if (pRet && pRet->init(275, 160, "Options"))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return nullptr;
}

void SelectMoreOptionsLayer::setup()
{
	auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();

	auto gameplaySprite = ButtonSprite::create("Gameplay", 120, true, "goldFont.fnt", "GJ_button_01.png", 0, 1.f);
	auto gameplayButton = CCMenuItemSpriteExtra::create(gameplaySprite, this, menu_selector(SelectMoreOptionsLayer::onSelectorButtonPressed));
	gameplayButton->setTag(1);
	m_pButtonMenu->addChild(gameplayButton);

	auto graphicsSprite = ButtonSprite::create("Graphics", 120, true, "goldFont.fnt", "GJ_button_01.png", 0, 1.f);
	auto graphicsButton = CCMenuItemSpriteExtra::create(graphicsSprite, this, menu_selector(SelectMoreOptionsLayer::onSelectorButtonPressed));
	graphicsButton->setTag(2);
	m_pButtonMenu->addChild(graphicsButton);

	auto editorSprite = ButtonSprite::create("Editor", 120, true, "goldFont.fnt", "GJ_button_01.png", 0, 1.f);
	auto editorButton = CCMenuItemSpriteExtra::create(editorSprite, this, menu_selector(SelectMoreOptionsLayer::onSelectorButtonPressed));
	editorButton->setTag(3);


	m_pButtonMenu->setPositionY(winSize.height / 2 - 10);

	m_pButtonMenu->addChild(editorButton);

	m_pButtonMenu->alignItemsVerticallyWithPadding(5.f);
}


bool SelectMoreOptionsLayer::init(float _w, float _h, std::string title)
{
	m_pLrSize = cocos2d::CCSize{ _w, _h };

	if (!this->initWithColor({ 0, 0, 0, 75 })) return false;
	this->m_pLayer = cocos2d::CCLayer::create();
	this->addChild(this->m_pLayer);

	this->setKeypadEnabled(true);
	this->setTouchEnabled(true);

	DIR->getTouchDispatcher()->incrementForcePrio(2);
	DIR->getTouchDispatcher()->addTargetedDelegate(this, -500, true);

	auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
	auto bg = cocos2d::extension::CCScale9Sprite::create("GJ_square01.png", { 0.0f, 0.0f, 80.0f, 80.0f });
	bg->setContentSize(m_pLrSize);
	bg->setPosition(winSize.width / 2, winSize.height / 2);
	this->m_pLayer->addChild(bg);

	this->m_pButtonMenu = cocos2d::CCMenu::create();
	this->m_pLayer->addChild(this->m_pButtonMenu);

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
	closeSpr->setScale(1.f);
	auto closeBtn = CCMenuItemSpriteExtra::create(
		closeSpr,
		this,
		(cocos2d::SEL_MenuHandler)&SelectMoreOptionsLayer::onClose
	);
	closeBtn->setUserData(reinterpret_cast<void*>(this));

	closeBtn->setPosition(-m_pLrSize.width / 2 + 10, m_pLrSize.height / 2);
	m_pButtonMenu->addChild(closeBtn);

	return true;
}


void SelectMoreOptionsLayer::onClose(CCObject* pSender)
{
	this->setKeyboardEnabled(false);
	this->removeFromParentAndCleanup(true);
}

FLAlertLayer* EditorOptionsLayer_create()
{
	return reinterpret_cast<FLAlertLayer* (__fastcall*)()>(
		base + 0x139D90
	)();
}

FLAlertLayer* VideoOptionsLayer_create()
{
	return reinterpret_cast<FLAlertLayer * (__fastcall*)()>(
		base + 0x1E0D70
	)();
}

void SelectMoreOptionsLayer::onSelectorButtonPressed(CCObject* pSender)
{
	switch (pSender->getTag())
	{
	// Gameplay
	case 1:
		MoreOptionsLayer::create()->show();
		break;
	// Graphics
	case 2:
		VideoOptionsLayer_create()->show();
		break;
	// Editor
	case 3:
		auto lr = EditorOptionsLayer_create();
		lr->m_bNoElasticity = false;
		lr->show();
		break;
	}
}