#include "PauseLayerHook.hpp"
#include "Callbacks.hpp"

bool PauseLayerHook::customSetup(gd::PauseLayer *self)
{
    if(!matdash::orig<&PauseLayerHook::customSetup>(self)) return false;

	auto winSize = CCDirector::sharedDirector()->getWinSize();
	int nodeCount = self->getChildrenCount();

	auto pauseBtn = gd::CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"), self, reinterpret_cast<SEL_MenuHandler>(&Callbacks::onOptionsLayerButtonPressed));
	pauseBtn->setScale(0.85f);
	pauseBtn->m_fBaseScale = 0.85f;
	
	auto m = CCMenu::create();
	m->setPosition(40, winSize.height - 40);
	m->addChild(pauseBtn);
	self->addChild(m);
	
	auto hideUIMenu = CCMenu::create();
	self->addChild(hideUIMenu, 11);

	hideUIMenu->setPosition({winSize.width - 40, winSize.height - 40});

	auto hideUIButton = gd::CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"), self, reinterpret_cast<SEL_MenuHandler>(&Callbacks::hidePauseLayerUI));
	hideUIButton->setUserObject(self);
	hideUIMenu->addChild(hideUIButton);

	bool isEditorLevel = MBO(int, MBO(void*, MBO(void*, gd::GameManager::sharedState(), 356), 1160), 868) == 2;
	
	for (int i = 0; i < nodeCount; i++)
	{
		auto nodes = reinterpret_cast<CCNode*>(self->getChildren()->objectAtIndex(i));
		
		if(!isEditorLevel)
		if(auto menu = dynamic_cast<CCMenu*>(nodes))
		{
			// idk any solutions both (with mhv7) have 4 children
			int menuCount = menu->getChildrenCount();
			for(int j = 0; j < menuCount; j++) 
			{
				//dynamic cast doesnt work for ccmenuitemspritextra for some reason?
				auto menubtn = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(menu->getChildren()->objectAtIndex(j));
				if(menubtn->getChildrenCount() == 1)
				{
					auto btnspr = reinterpret_cast<CCSprite*>(menubtn->getChildren()->objectAtIndex(0));					
					const char* tname = getTextureName(btnspr);

					std::cout << j << ' ' << tname << std::endl;

					if(strcmp(tname, "GJ_playBtn2_001.png") == 0)
					{
						auto infoButton = gd::CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png"), self, menu_selector(Callbacks::onPauseLayerInfoPressed));
						infoButton->setScale(1.3f);
						infoButton->m_fBaseScale = 1.3f;
						infoButton->setPositionX(-209.f);
						
						//insert child manually at index 0 (left) 
						menu->getChildren()->insertObject(infoButton, 0);
						infoButton->setParent(menu);
						infoButton->onEnter();
						infoButton->onEnterTransitionDidFinish();
						menu->alignItemsHorizontallyWithPadding(15.0f);
						break;
					}
				}
			}
		}
		//if the above was true there is no need to check again, a node cant be more than 1 type at the same time
		else if(auto label = dynamic_cast<CCLabelBMFont*>(nodes))
		{
			if(label->getPositionY() == 75.f)
			{
				label->setVisible(false);
			}
		}

		else if(auto slider = dynamic_cast<CCLayer*>(nodes))
		{
			if(slider->getPositionY() == 55.f)
			{
				slider->setVisible(false);
			}
		}
	}

	return true;
}

// IDK what the actual function is called in gd, just called it onPracticeEnd myself (sub_5E5F60)
void PauseLayerHook::onPracticeEnd(gd::PauseLayer *self, cocos2d::CCObject *pSender)
{
	auto protocol = PracticeFLProtocol::create(self);
	gd::FLAlertLayer::create(protocol, "Exit Practice Mode", "Cancel", "OK", "You are about to exit <cb>practice mode</c>, do you want to <cr>exit</c>?")->show();
}

void PauseLayerHook::LoadHooks()
{
    matdash::add_hook<&PauseLayerHook::customSetup>(gd::base + 0x1E4620);
    std::cout << "Hooked PauseLayer::customSetup" << std::endl;

	matdash::add_hook<&PauseLayerHook::onPracticeEnd>(gd::base + 0x1E5F60);
    std::cout << "Hooked PauseLayer::onPracticeEnd" << std::endl;
}