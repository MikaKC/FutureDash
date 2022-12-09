#include "MenuLayerHook.hpp"
#include "PlayerInfoLayer.hpp"

bool MenuLayerHook::init(gd::MenuLayer *self)
{
	if (!matdash::orig<&MenuLayerHook::init>(self)) return false;

	auto infoButton = gd::CCMenuItemSpriteExtra::create(
		CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
		self,
		(SEL_MenuHandler)(&MenuLayerHook::onPlayerInfo)
	);

	infoButton->setScale(0.75f);
	infoButton->m_fBaseScale = 0.75f;
	infoButton->m_fScaleMultiplier = 1.25f;

	auto menu = CCMenu::create();
	menu->addChild(infoButton);
	menu->setPosition({83, 123});

	self->addChild(menu);

	return true;
}

void MenuLayerHook::onPlayerInfo(cocos2d::CCObject* pSender)
{
	PlayerInfoLayer::create()->show();
}

void MenuLayerHook::LoadHooks()
{
	matdash::add_hook<&MenuLayerHook::init>(gd::base + 0x1907B0);
	std::cout << "Hooked MenuLayer::init" << std::endl;
}