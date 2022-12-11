#include "CreditsLayer.hpp"

CreditsLayer* CreditsLayer::create()
{
	auto ptr = new (std::nothrow) CreditsLayer;
	if(ptr && ptr->init(300, 150, "Credits"))
	{
		ptr->autorelease();
		return ptr;
	}

	CC_SAFE_DELETE(ptr);
	return nullptr;
}


void CreditsLayer::setup()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	auto visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	
	auto menu = CCMenu::create();
	menu->setPosition(ccp(0, 0));

	auto iAndyIcon = SimplePlayer::create(30);
	iAndyIcon->setPosition({winSize.width / 2 - m_pLrSize.width / 2 + 40, winSize.height / 2 + 25});
	iAndyIcon->setColor(GM->colorForIdx(12));
	iAndyIcon->setSecondColor(GM->colorForIdx(11));

	auto iAndyText = CCLabelBMFont::create("iAndyHD", "goldFont.fnt");
	iAndyText->setScale(0.5f);

	auto iAndyContrib = CCLabelBMFont::create("Programming, extra help", "chatFont.fnt");
	iAndyContrib->setScale(0.85f);

	iAndyContrib->setPosition({winSize.width / 2 - m_pLrSize.width / 2 + 127.5f, winSize.height / 2 + 18.f});

	// This shit doesn't work
	auto iAndyBtn = CCMenuItemSpriteExtra::create(iAndyText, this, menu_selector(CreditsLayer::onIconClicked));
	iAndyBtn->setTag(1);
	iAndyBtn->setPosition({winSize.width / 2 - m_pLrSize.width / 2 + 83.f, winSize.height / 2 + 32});

	menu->addChild(iAndyBtn);
	menu->addChild(iAndyIcon);

	auto matIcon = SimplePlayer::create(133);
	matIcon->setPosition({winSize.width / 2 - m_pLrSize.width / 2 + 40, winSize.height / 2 - 12.5f});
	matIcon->setColor(GM->colorForIdx(41));
	matIcon->setSecondColor(GM->colorForIdx(40));
	matIcon->setGlowOutline(true);

	auto matText = CCLabelBMFont::create("mat", "goldFont.fnt");
	matText->setScale(0.75f);

	auto matContrib = CCLabelBMFont::create("Matdash library, extra help", "chatFont.fnt");
	matContrib->setScale(0.85f);
	matContrib->setPosition({winSize.width / 2 - m_pLrSize.width / 2 + 130, winSize.height / 2 - 23.f});

	// This shit doesn't work
	auto matBtn = CCMenuItemSpriteExtra::create(matText, this, menu_selector(CreditsLayer::onIconClicked));
	matBtn->setTag(2);
	matBtn->setPosition({winSize.width / 2 - m_pLrSize.width / 2 + 75, winSize.height / 2 - 5.f});
	
	menu->addChild(matBtn);
	menu->addChild(matIcon);

	auto pieIcon = SimplePlayer::create(20);
	pieIcon->setPosition({winSize.width / 2 - m_pLrSize.width / 2 + 40, winSize.height / 2 - 50});
	pieIcon->setColor(GM->colorForIdx(10));
	pieIcon->setSecondColor(GM->colorForIdx(12));
	pieIcon->setGlowOutline(true);

	auto pieText = CCLabelBMFont::create("Pie", "goldFont.fnt");
	pieText->setScale(0.75f);

	auto pieContrib = CCLabelBMFont::create("Extra help", "chatFont.fnt");
	pieContrib->setScale(0.85f);
	pieContrib->setPosition({winSize.width / 2 - m_pLrSize.width / 2 + 85, winSize.height / 2 -57});

	// This shit doesn't work
	auto pieBtn = CCMenuItemSpriteExtra::create(pieText, this, menu_selector(CreditsLayer::onIconClicked));
	pieBtn->setTag(3);
	pieBtn->setPosition({winSize.width / 2 - m_pLrSize.width / 2 + 75, winSize.height / 2 -43});
	
	menu->addChild(pieBtn);
	menu->addChild(pieIcon);

	menu->addChild(iAndyContrib);
	menu->addChild(matContrib);
	menu->addChild(pieContrib);


	m_pLayer->addChild(menu);
}

bool CreditsLayer::init(float _w, float _h, std::string title)
{
	auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
	m_pLrSize = cocos2d::CCSize { _w, _h };

	if (!this->initWithColor({ 0, 0, 0, 75 })) return false;
	
	this->setKeypadEnabled(true);
	this->setTouchEnabled(true);
	auto dir = CCDirector::sharedDirector();
	dir->getTouchDispatcher()->incrementForcePrio(2);
	dir->getTouchDispatcher()->addTargetedDelegate(this, -500, true);
	
	this->m_pLayer = cocos2d::CCLayer::create();
	this->addChild(this->m_pLayer);

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
		(cocos2d::SEL_MenuHandler)&CreditsLayer::onClose
	);
	closeBtn->setUserData(reinterpret_cast<void*>(this));

	this->m_pButtonMenu->addChild(closeBtn);

	closeBtn->setPosition( - _w / 2 + 10, _h / 2 - 10);


	return true;
}

// This shit doesn't work
void CreditsLayer::onIconClicked(cocos2d::CCObject* pSender)
{

	switch(pSender->getTag())
	{
		// Info Badges
		case 1:
			ProfilePage::create(1688850, false)->show();
		break;
		case 2:
			ProfilePage::create(5568872, false)->show();
		break;
		case 3:
			ProfilePage::create(2878941, false)->show();
		break;
	}
}

void CreditsLayer::onClose(cocos2d::CCObject *self)
{
	this->setKeyboardEnabled(false);
	this->removeFromParentAndCleanup(true);
}

