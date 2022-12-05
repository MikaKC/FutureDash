#include "includes.h"
#include "InfoLayer.hpp"
#include "Callbacks.hpp"

// Release
#define DEBUG

#ifdef DEBUG
    #include <matdash/console.hpp>
#endif

#include <matdash.hpp>
#include <matdash/minhook.hpp>
#include <matdash/boilerplate.hpp>

bool MenuLayer_init(gd::MenuLayer* self) {

    if (!matdash::orig<&MenuLayer_init>(self)) return false;

    auto infoButton = gd::CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
        self,
        reinterpret_cast<SEL_MenuHandler>(&Callbacks::onInfoButtonPressed)
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

matdash::cc::thiscall<void> LoadingLayer_loadAssets(gd::LoadingLayer* self)
{
  matdash::orig<&LoadingLayer_loadAssets>(self);

  // Load sprite sheets n stuff
  return {};
}

bool PauseLayer_customSetup(gd::PauseLayer* self)
{
    if(!matdash::orig<&PauseLayer_customSetup>(self)) return false;

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    int nodeCount = self->getChildrenCount();

    auto infoButton = gd::CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png"), self, nullptr);
    infoButton->setScale(1.3f);
    infoButton->m_fBaseScale = 1.3f;
    infoButton->setPositionX(-209.f);

    auto settingsBtn = gd::CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"), self, reinterpret_cast<SEL_MenuHandler>(&Callbacks::onOptionsLayerButtonPressed));
    settingsBtn->setPosition({winSize.width / 2 - 85, winSize.height / 2 - 20});


    for (int i = 0; i < nodeCount; i++)
    {
        auto nodes = reinterpret_cast<CCNode*>(self->getChildren()->objectAtIndex(i));

        if(auto menu = dynamic_cast<CCMenu*>(nodes))
        {
            // idk any solutions both (with mhv7) have 4 children
            if(menu->getPosition().x == 284.5f && menu->getPosition().y == 130.f)
            {
                if(menu->getChildrenCount() == 5)
                {
                    std::cout << "Playtest";
                    menu->setPositionX(284.5f);
                    // repositionner
                    settingsBtn->setPositionX(winSize.width / 2 - 49.5f);
                    
                    infoButton->setVisible(false);
                } 
                else {
                    std::cout << "Game";
                    menu->setPositionX(320.f);
                    menu->addChild(infoButton);
                    menu->addChild(settingsBtn);
                }

                menu->addChild(infoButton);
                menu->addChild(settingsBtn);
            }
        }

        if(auto label = dynamic_cast<CCLabelBMFont*>(nodes))
        {
            if(label->getPositionY() == 75.f)
            {
                label->setVisible(false);
            }
        }

        if(auto slider = dynamic_cast<CCLayer*>(nodes))
        {
            if(slider->getPositionY() == 55.f)
            {
                slider->setVisible(false);
            }
        }
    }

    return true;
}


const char* getTextureName(CCSprite* sprite_node) {
	
		auto* texture = sprite_node->getTexture();
		CCDictElement* el;
		
		auto* frame_cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		auto* cached_frames = public_cast(frame_cache, m_pSpriteFrames);
		const auto rect = sprite_node->getTextureRect();
		CCDICT_FOREACH(cached_frames, el) {
			auto* frame = static_cast<CCSpriteFrame*>(el->getObject());
			if (frame->getTexture() == texture && frame->getRect().equals(rect)) {
				return el->getStrKey();
			}
		}
	return "";
}


bool LevelInfoLayer_init(gd::LevelInfoLayer* self, gd::GJGameLevel* level)
{
    if(!matdash::orig<&LevelInfoLayer_init>(self, level)) return false;

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


	for(int i = 0; i < self->getChildrenCount(); i++)
	{
		CCObject* o = self->getChildren()->objectAtIndex(i);	
		if(auto s = dynamic_cast<CCSprite*>(o)) 
		{
			
			auto tname = getTextureName(s);
			std::cout << i << ' ' << tname << std::endl;
			
			int num = 0;
			if(strcmp(tname, "highObjectIcon_001.png") == 0) num = 1;
			else if(strcmp(tname, "collaborationIcon_001.png") == 0) num = 2;
			
			if(num != 0)
			{
				auto newspr = CCSprite::createWithSpriteFrameName(tname);
				newspr->setScale(s->getScale());
				auto btn = gd::CCMenuItemSpriteExtra::create(newspr, self, menu_selector(Callbacks::onLevelBadgeInfo));
				btn->setTag(num);
				auto menu = CCMenu::create();
				menu->setPosition(s->getPosition());
				menu->addChild(btn);
				self->addChild(menu);
				s->setVisible(false);
			}
		}
	}

    return true;
}



void mod_main(HMODULE)
{
	#ifdef DEBUG
		if(AllocConsole())
		{
#pragma warning(push, 0)
			freopen("CONOUT$", "wt", stdout);
			freopen("CONIN$", "rt", stdin);
#pragma warning(pop)
			std::ios::sync_with_stdio(1);
		}
	#endif
	
    std::cout << "Hello World" << std::endl;

    // Hooks
    matdash::add_hook<&LevelInfoLayer_init>(gd::base + 0x175df0);
    std::cout << "Hooked LevelInfoLayer::init" << std::endl;

    matdash::add_hook<&MenuLayer_init>(gd::base + 0x1907b0);
    std::cout << "Hooked MenuLayer::init" << std::endl;

    matdash::add_hook<&PauseLayer_customSetup>(gd::base + 0x1E4620);
    std::cout << "Hooked PauseLayer::customSetup" << std::endl;
    
    matdash::add_hook<&LoadingLayer_loadAssets>(gd::base + 0x18C8E0);
    std::cout << "Hooked LoadingLayer::loadAssets" << std::endl;

    std::cout << "Finished hooking" << std::endl;
}