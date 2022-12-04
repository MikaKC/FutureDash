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

bool PauseLayer_init(gd::PauseLayer* self)
{
    if(!matdash::orig<&PauseLayer_init>(self)) return false;

    // TODO: Implement GJGameLevel or something 

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    int nodeCount = self->getChildrenCount();

    auto infoButton = gd::CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png"), self, nullptr);
    infoButton->setScale(1.3f);
    infoButton->m_fBaseScale = 1.3f;
    infoButton->setPositionX(-209.f);

    // créer le bouton 
    auto settingsBtn = gd::CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"), self, reinterpret_cast<SEL_MenuHandler>(&Callbacks::onOptionsLayerButtonPressed));
    // positionner le bouton dans le CCMenu
    settingsBtn->setPosition({winSize.width / 2 - 85, winSize.height / 2 - 20});


    for (int i = 0; i < nodeCount; i++)
    {
        auto nodes = reinterpret_cast<CCNode*>(self->getChildren()->objectAtIndex(i));

        if(auto menu = dynamic_cast<CCMenu*>(nodes))
        {
            // idk any solutions both (with mhv7) have 4 children
            if(menu->getPosition().x == 284.5f && menu->getPosition().y == 130.f)
            {
                if(menu->getChildrenCount() >= 5)
                {
                    menu->setPositionX(284.5f);
                    settingsBtn->setPositionX(winSize.width / 2 - 49.5f);
                    infoButton->setVisible(false);
                    menu->addChild(infoButton);
                    menu->addChild(settingsBtn);
                } else {
                    menu->setPositionX(320.f);
                    menu->addChild(infoButton);
                    menu->addChild(settingsBtn);
                }

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

bool LevelInfoLayer_init(gd::LevelInfoLayer* self, gd::GJGameLevel* level)
{
    if(!matdash::orig<&LevelInfoLayer_init>(self, level)) return false;

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto pauseBtn = gd::CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"), self, reinterpret_cast<SEL_MenuHandler>(&Callbacks::onMoreOptionsLayerButtonPressed));
    
    pauseBtn->setPosition({-210, winSize.height / 2 - 25});
    pauseBtn->setScale(0.85f);
    pauseBtn->m_fBaseScale = 0.85f;

    self->m_pPlayBtnMenu->addChild(pauseBtn);

    return true;
}

void mod_main(HMODULE)
{
	#ifdef DEBUG
		if(AllocConsole())
		{
			freopen("CONOUT$", "wt", stdout);
			freopen("CONIN$", "rt", stdin);
			std::ios::sync_with_stdio(1);
		}
	#endif
	
    std::cout << "Hello World" << std::endl;

    // Hooks
    matdash::add_hook<&LevelInfoLayer_init>(gd::base + 0x175df0);
    std::cout << "Hooked LevelInfoLayer::init" << std::endl;

    matdash::add_hook<&MenuLayer_init>(gd::base + 0x1907b0);
    std::cout << "Hooked MenuLayer::init" << std::endl;

    matdash::add_hook<&PauseLayer_init>(gd::base + 0x1E4626);
    std::cout << "Hooked PauseLayer::init" << std::endl;
    
    matdash::add_hook<&LoadingLayer_loadAssets>(gd::base + 0x18C8E0);
    std::cout << "Hooked LoadingLayer::loadAssets" << std::endl;

    std::cout << "Finished hooking" << std::endl;
}
