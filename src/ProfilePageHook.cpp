#include "ProfilePageHook.hpp"

void ProfilePageHook::loadPageWithUserInfo(ProfilePage *self, GJUserScore *score)
{
	matdash::orig<&ProfilePageHook::loadPageWithUserInfo>(self, score);

	auto layer = reinterpret_cast<CCLayer*>(self->getChildren()->objectAtIndex(0));
	
	auto menu = CCMenu::create();
	menu->setPosition({0, 0});
	layer->addChild(menu);

	for(unsigned int i = 0; i < layer->getChildrenCount(); i++)
	{
		CCObject* o = layer->getChildren()->objectAtIndex(i);
		if(auto s = dynamic_cast<CCSprite*>(o)) 
		{
			
			auto tname = ModToolbox::getTextureNameForSpriteFrame(s);
			std::cout << i << ' ' << tname << std::endl;
			
			int num = 0;
			if(strcmp(tname, "modBadge_01_001.png") == 0) num = 1;
			else if(strcmp(tname, "modBadge_02_001.png") == 0) num = 2;
			
			if(num != 0)
			{
				auto newspr = CCSprite::createWithSpriteFrameName(tname);
				newspr->setScale(s->getScale());
				auto btn = CCMenuItemSpriteExtra::create(newspr, self, menu_selector(ProfilePageHook::onModeratorBadgeInfo));
				btn->setTag(num);
				btn->setPosition(s->getPosition());
				menu->addChild(btn);
				s->setVisible(false);
			}
		}
	}
}

void ProfilePageHook::onModeratorBadgeInfo(cocos2d::CCObject* pSender)
	{
		switch(pSender->getTag())
		{
			// Moderator Badges
			case 1:
				ALERT("Badge", "OK", nullptr, "This user is a <cy>Moderator</c>, they can send levels to RobTop.");
			break;
			case 2:
				ALERT("Badge", "OK", nullptr, "This user is an <cr>Elder Moderator</c>, they can send level to RobTop <cb>and</c> moderate chats.");
			break;
		}
	}
	
void ProfilePageHook::LoadHooks()
{
	matdash::add_hook<&ProfilePageHook::loadPageWithUserInfo>(base + 0x210040);
	std::cout << "Hooked ProfilePage::loadWithUserInfo" << std::endl;
}