#include "MenuLayerHook.hpp"
#include "PlayerInfoLayer.hpp"

bool MenuLayerHook::init_()
{
	if (!matdash::orig<&MenuLayerHook::init_>(this)) return false;
	
	
	this->replaceAccountButton();
	
	auto infoButton = CCMenuItemSpriteExtra::create(
		CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
		this,
		(SEL_MenuHandler)(&MenuLayerHook::onPlayerInfo)
	);
	
	infoButton->setScale(0.75f);
	infoButton->m_fBaseScale = 0.75f;
	infoButton->m_fScaleMultiplier = 1.25f;

	auto menu = CCMenu::create();
	menu->addChild(infoButton);
	menu->setPosition({83, 123});

	this->addChild(menu);

	return true;
}

void MenuLayerHook::replaceAccountButton()
{
	int count = this->getChildrenCount();
	for(int i = 0; i < count; i++)
	{
		auto node = (CCNode*)this->getChildren()->objectAtIndex(i);
		if(auto menu = dynamic_cast<CCMenu*>(node))
		{
			int menuCount = menu->getChildrenCount();
			for(int j = 0; j <	menuCount; j++)
			{
				auto button = (CCMenuItemSpriteExtra*)menu->getChildren()->objectAtIndex(j);
				auto spr = (CCSprite*)button->getChildren()->objectAtIndex(0);
				if(strcmp(ModToolbox::getTextureName(spr), "GJ_profileButton_001.png") == 0) 
				{
					m_pProfileIconSprite = SimplePlayer::create(0);
					m_pProfileIconSprite->updatePlayerFrame(ModToolbox::frameForIcon(GM->getPlayerIconType()), GM->getPlayerIconType());
					m_pProfileIconSprite->setColor(GM->colorForIdx(GM->getPlayerColor()));
					m_pProfileIconSprite->setSecondColor(GM->colorForIdx(GM->getPlayerColor2()));
					m_pProfileIconSprite->setGlowOutline(GM->getPlayerGlow());
					spr->addChild(m_pProfileIconSprite);
					spr->setDisplayFrame(m_pProfileIconSprite->displayFrame());
					return;
				}
			}
		}
	}
}

void MenuLayerHook::onPlayerInfo(cocos2d::CCObject* pSender)
{
	PlayerInfoLayer::create(this)->show();
}

void MenuLayerHook::LoadHooks()
{
	matdash::add_hook<&MenuLayerHook::init_>(base + 0x1907B0);
	std::cout << "Hooked MenuLayer::init" << std::endl;
}