#include "LevelInfoLayerHook.hpp"
#include "ModToolbox.hpp"
#include "SelectMoreOptionsLayer.h"

bool LevelInfoLayerHook::initHook(GJGameLevel* level)
{
	if(!matdash::orig<&LevelInfoLayerHook::initHook>(this, level)) return false;

	auto winSize = CCDirector::sharedDirector()->getWinSize();
	auto visSize = CCDirector::sharedDirector()->getVisibleSize();

	auto optionsBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"), this, (SEL_MenuHandler)(&LevelInfoLayerHook::onMoreOptionsLayerButtonPressed));
	optionsBtn->setScale(0.85f);
	optionsBtn->m_fBaseScale = 0.85f;
	
	auto m = CCMenu::create();
	m->setPosition(75, winSize.height - 25);
	m->addChild(optionsBtn);
	this->addChild(m);

	auto menu = CCMenu::create();
	menu->setPosition({0, 0});
	this->addChild(menu);

	for(unsigned int i = 0; i < this->getChildrenCount(); i++)
	{
		CCObject* o = this->getChildren()->objectAtIndex(i);	
		if(auto s = dynamic_cast<CCSprite*>(o)) 
		{
			
			auto tname = ModToolbox::getTextureNameForSpriteFrame(s);
			std::cout << i << ' ' << tname << std::endl;
			
			int num = 0;

			auto untouchedPosition = s->getPosition();

			if(strcmp(tname, "highObjectIcon_001.png") == 0) num = 1;
			else if(strcmp(tname, "collaborationIcon_001.png") == 0) num = 2;
			else if(s->isVisible() == true && (strcmp(tname, "GJ_featuredCoin_001.png") == 0)) 
			{
				num = 3;
				s->setTag(120);
			}
			else if(strcmp(tname, "GJ_epicCoin_001.png") == 0)
			{
				num = 4;
				s->setTag(121);
			}

			if(num != 0)
			{
				s->setVisible(false);

				auto newspr = CCSprite::createWithSpriteFrameName(tname);
				newspr->setScale(s->getScale());
				auto btn = CCMenuItemSpriteExtra::create(newspr, this, menu_selector(LevelInfoLayerHook::onLevelBadgeInfo));
				btn->setTag(num);
				btn->setPosition(untouchedPosition);

				menu->addChild(btn);
			}
		}
	}

	return true;
}

void LevelInfoLayerHook::onMoreOptionsLayerButtonPressed(cocos2d::CCObject* pSender)
{
	SelectMoreOptionsLayer::create()->show();
}

void LevelInfoLayerHook::onLevelBadgeInfo(cocos2d::CCObject* pSender)
{
	switch (pSender->getTag())
	{
		// Info Badges
		case 1:
			ALERT("High Object Count", "OK", nullptr, "This level has more than <cr>40K</c> objects");
		break;
		case 2:
			ALERT("Collab", "OK", nullptr, "This level is a collab or has been copied");
		break;

			// Feature Badges
		case 3:
			ALERT("Featured", "OK", nullptr, "This level has been <cy>featured</c> by RobTop.");
		break;
		case 4:
			ALERT("Epic", "OK", nullptr, "This level has been <co>epic</c> featured by RobTop.");
		break;
	}
}
	

void LevelInfoLayerHook::updateLabelValuesHook()
{
	matdash::orig<&LevelInfoLayerHook::updateLabelValuesHook>(this);

	CCObject* node;

	CCARRAY_FOREACH(this->getChildren(), node)
	{
		if(auto spr = dynamic_cast<CCSprite*>(node))
		{
			switch (spr->getTag())
			{
			case 120:
				spr->setVisible(false);
				break;
			case 121:
				spr->setVisible(false);
				break;
			
			default:
				break;
			}
		}
	}
}

void LevelInfoLayerHook::LoadHooks()
{
	matdash::add_hook<&LevelInfoLayerHook::initHook>(base + 0x175DF0);
	std::cout << "Hooked LevelInfoLayer::init" << std::endl;

	matdash::add_hook<&LevelInfoLayerHook::updateLabelValuesHook>(base + 0x17B170);
	std::cout << "Hooked LevelInfoLayer::updateLabelValues" << std::endl;
}