#include "LevelInfoLayerHook.hpp"

bool LevelInfoLayerHook::init(gd::LevelInfoLayer* self, gd::GJGameLevel* level)
{
    if(!matdash::orig<&LevelInfoLayerHook::init>(self, level)) return false;

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto visSize = CCDirector::sharedDirector()->getVisibleSize();

    auto pauseBtn = gd::CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"), self, reinterpret_cast<SEL_MenuHandler>(&Callbacks::onMoreOptionsLayerButtonPressed));
	pauseBtn->setScale(0.85f);
    pauseBtn->m_fBaseScale = 0.85f;
	
	
   // pauseBtn->setPosition({winSize.width * 0.15f, winSize.height - 25});
 

	auto m = CCMenu::create();
	m->setPosition(75, winSize.height - 25);
	m->addChild(pauseBtn);
	self->addChild(m);

	auto menu = CCMenu::create();
	menu->setPosition({0, 0});
    self->addChild(menu);

	for(unsigned int i = 0; i < self->getChildrenCount(); i++)
	{
		CCObject* o = self->getChildren()->objectAtIndex(i);	
		if(auto s = dynamic_cast<CCSprite*>(o)) 
		{
			
			auto tname = getTextureName(s);
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
				auto btn = gd::CCMenuItemSpriteExtra::create(newspr, self, menu_selector(Callbacks::onLevelBadgeInfo));
				btn->setTag(num);
                btn->setPosition(untouchedPosition);

	            menu->addChild(btn);
			}
		}
	}

    return true;
}

void LevelInfoLayerHook::updateLabelValues(gd::LevelInfoLayer* self)
{
    matdash::orig<&LevelInfoLayerHook::updateLabelValues>(self);

    CCObject* node;

    CCARRAY_FOREACH(self->getChildren(), node)
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
    matdash::add_hook<&LevelInfoLayerHook::init>(gd::base + 0x175DF0);
    std::cout << "Hooked LevelInfoLayer::init" << std::endl;

    matdash::add_hook<&LevelInfoLayerHook::updateLabelValues>(gd::base + 0x17B170);
    std::cout << "Hooked LevelInfoLayer::updateLabelValues" << std::endl;
}