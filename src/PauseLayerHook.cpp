#include "PauseLayerHook.hpp"

bool PauseLayerHook::customSetup(PauseLayer *self)
{
	if(!matdash::orig<&PauseLayerHook::customSetup>(self)) return false;

	CCDirector *dir = CCDirector::sharedDirector();
	
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	int nodeCount = self->getChildrenCount();

	auto pauseBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"), self, (SEL_MenuHandler)(&PauseLayerHook::onOptions));
	pauseBtn->setScale(0.85f);
	pauseBtn->m_fBaseScale = 0.85f;
	
	auto m = CCMenu::create();
	m->setPosition(40, winSize.height - 40);
	m->addChild(pauseBtn);
	self->addChild(m);
	
	auto hideUIMenu = CCMenu::create();
	self->addChild(hideUIMenu, 11);

	hideUIMenu->setPosition({winSize.width - 40, winSize.height - 40});

	auto hideUIButton = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"), self, (SEL_MenuHandler)(&PauseLayerHook::onHideUI));
	hideUIButton->setUserObject(self);
	hideUIMenu->addChild(hideUIButton);

	// By User
	std::string robtopTopala = (PlayLayer::get()->m_level->m_sCreatorName == "" && 
	PlayLayer::get()->m_level->m_nLevelID ==  1 || 
	PlayLayer::get()->m_level->m_nLevelID ==  2 ||
	PlayLayer::get()->m_level->m_nLevelID ==  3 ||
	PlayLayer::get()->m_level->m_nLevelID ==  4 ||
	PlayLayer::get()->m_level->m_nLevelID ==  5 ||
	PlayLayer::get()->m_level->m_nLevelID ==  6 ||
	PlayLayer::get()->m_level->m_nLevelID ==  7 ||
	PlayLayer::get()->m_level->m_nLevelID ==  8 ||
	PlayLayer::get()->m_level->m_nLevelID ==  9 ||
	PlayLayer::get()->m_level->m_nLevelID ==  10||
	PlayLayer::get()->m_level->m_nLevelID ==  11||
	PlayLayer::get()->m_level->m_nLevelID ==  12||
	PlayLayer::get()->m_level->m_nLevelID ==  13||
	PlayLayer::get()->m_level->m_nLevelID ==  14||
	PlayLayer::get()->m_level->m_nLevelID ==  15||
	PlayLayer::get()->m_level->m_nLevelID ==  16||
	PlayLayer::get()->m_level->m_nLevelID ==  17||
	PlayLayer::get()->m_level->m_nLevelID ==  18||
	PlayLayer::get()->m_level->m_nLevelID ==  19||
	PlayLayer::get()->m_level->m_nLevelID ==  20||
	PlayLayer::get()->m_level->m_nLevelID == 21) ? "RobTopGames" : "Player";

	std::string creatorNameString = ((PlayLayer::get()->m_level->m_sCreatorName == "") ? robtopTopala : PlayLayer::get()->m_level->m_sCreatorName);
	auto authorText = CCLabelBMFont::create(std::format("By {}", creatorNameString).c_str(), "goldFont.fnt");
	self->addChild(authorText, 11);
	// change by the left
	authorText->setAlignment(CCTextAlignment::kCCTextAlignmentLeft);
	authorText->setPosition({winSize.width / 2, 265});

	bool isEditorLevel = MBO(int, MBO(void*, MBO(void*, GM, 356), 1160), 868) == 2;

	auto slidersMenu = CCMenu::create();
	self->addChild(slidersMenu, 3);
	slidersMenu->setPosition({0, 0});

	for (int i = 0; i < nodeCount; i++)
	{
		auto nodes = reinterpret_cast<CCNode*>(self->getChildren()->objectAtIndex(i));
		
		if(!isEditorLevel)
		if(auto menu = dynamic_cast<CCMenu*>(nodes))
		{
			int menuCount = menu->getChildrenCount();
			for(int j = 0; j < menuCount; j++) 
			{
				//dynamic cast doesnt work for ccmenuitemspritextra for some reason?
				auto menubtn = reinterpret_cast<CCMenuItemSpriteExtra*>(menu->getChildren()->objectAtIndex(j));

				if(menubtn->getChildrenCount() == 1)
				{
					auto btnspr = reinterpret_cast<CCSprite*>(menubtn->getChildren()->objectAtIndex(0));			
					const char* tname = ModToolbox::getTextureNameForSpriteFrame(btnspr);

					menu->setPositionY(200);

					std::cout << j << ' ' << tname << std::endl;

					if(strcmp(tname, "GJ_playBtn2_001.png") == 0)
					{
						auto infoButton = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png"), self, (SEL_MenuHandler)(&PauseLayerHook::onInfoLayer));
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

		// these got excluded by (!isEditorLevel)
		if(auto label = dynamic_cast<CCLabelBMFont*>(nodes))
		{
			// Theres probably a way better way to do this but whatever
			if(strcmp(label->getString(), "SFX") == 0)
			{
				label->setVisible(false);
			}
			else if(strcmp(label->getString(), "Music") == 0)
			{
				label->setVisible(false);
			}
			// we shouldn't really check for positions its not that good and prob can cause a bunch a bugs but this is what we do now ig
			else if(strcmp(label->getString(), std::format("{}%", PlayLayer::get()->m_level->m_nPracticePercent).c_str()) == 0 && label->getPositionY() == 190)
			{
				label->setPositionY(80);
			}
			else if(strcmp(label->getString(), std::format("{}%", PlayLayer::get()->m_level->m_nNormalPercent).c_str()) == 0 && label->getPositionY() == 240)
			{
				label->setPositionY(130);
			}
			else if(strcmp(label->getString(), "Normal Mode") == 0)
			{
				label->setPositionY(152);
			}
			else if(strcmp(label->getString(), "Practice Mode") == 0)
			{
				label->setPositionY(100);
			}
		}
		else if(auto slider = dynamic_cast<CCLayer*>(nodes))
		{
			if(slider->getPositionY() == 55.f)
			{
				slider->setVisible(false);
			}
		} 
		else if(auto sprite = dynamic_cast<CCSprite*>(nodes))
		{
			// returns the full path to the spr
			std::string tname = ModToolbox::getTextureNameForSprite(sprite);
			std::string pathToResources = CCFileUtils::sharedFileUtils()->getSearchPaths()[0] + "Resources/";

			// I have no idea what i did
			if(tname.find(pathToResources) != std::string::npos)
				tname.erase(0, pathToResources.length());

			std::cout << i << ' ' << tname << std::endl;

			if(strcmp(tname.c_str(), "GJ_progressBar_001.png") == 0 || strcmp(tname.c_str(), "GJ_progressBar_001-hd.png") == 0 || strcmp(tname.c_str(), "GJ_progressBar_001-uhd.png") == 0)
			{
				auto childSpr = reinterpret_cast<CCSprite*>(sprite->getChildren()->objectAtIndex(0));
				if(childSpr->getColor().r == 0 && childSpr->getColor().g == 255 && childSpr->getColor().b == 255)
				{

					// practice
					sprite->setPositionY(80);
				} else {

					// normal
					sprite->setPositionY(130);
				}
			}
		}
	}

	return true;
}

void PauseLayerHook::onPracticeEnd(PauseLayer *self, cocos2d::CCObject *pSender)
{
	if(!GM->getGameVariable("2302"))
	{
		auto protocol = PracticeFLProtocol::create(self);
		FLAlertLayer::create(protocol, "Exit", "NO", "YES", "<cr>Exit</c> practice mode?")->show();
	} else {
		matdash::orig<&PauseLayerHook::onPracticeEnd>(self, pSender);
	}
}

void PauseLayerHook::onOptions(cocos2d::CCObject* pSender)
{
	auto layer = OptionsLayer::create();
	cocos2d::CCDirector::sharedDirector()->getRunningScene()->addChild(layer, 100);
	layer->showLayer(false);
}

void PauseLayerHook::onHideUI(cocos2d::CCObject* pSender)
{
   PauseLayer* self = static_cast<PauseLayer*>(((CCNode*)pSender)->getUserObject());
   self->setVisible(false);
}

void PauseLayerHook::LoadHooks()
{
	matdash::add_hook<&PauseLayerHook::customSetup>(base + 0x1E4620);
	std::cout << "Hooked PauseLayer::customSetup" << std::endl;

	matdash::add_hook<&PauseLayerHook::onPracticeEnd>(base + 0x1E5F60);
	std::cout << "Hooked PauseLayer::onPracticeEnd" << std::endl;

	matdash::add_hook<&PauseLayerHook::onPracticeEnd>(base + 0x1E5F60);
	std::cout << "Hooked PauseLayer::onPracticeEnd" << std::endl;
}



// Since hj's headers don't have this func, we add it ourselves
FLAlertLayer* PauseLayerHook::createInfoLayer(GJGameLevel* level)
{
	return reinterpret_cast<FLAlertLayer*(__fastcall*)(GJGameLevel*, GJUserScore*)>(
		base + 0x14F4F0
	)(level, nullptr);
}

void PauseLayerHook::onInfoLayer(cocos2d::CCObject* pSender)
{
	PauseLayerHook::createInfoLayer(PlayLayer::get()->m_level)->show();
}
	
	
	
//PracticeFLProtocol


PracticeFLProtocol* PracticeFLProtocol::create(PauseLayer *lr)
{
	PracticeFLProtocol *pRet = new PracticeFLProtocol(lr);
	if (pRet)
	{
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void PracticeFLProtocol::PauseLayer_onResume(PauseLayer *self, bool a2)
{
	// needed __thiscall* not __fastcall*
	reinterpret_cast<void(__thiscall*)(PauseLayer*, bool)>(
		base + 0x1E5FA0
	)(self, a2);
}

void PracticeFLProtocol::FLAlert_Clicked(FLAlertLayer* other, bool btn2)
{
	if(!btn2)
	{
		other->setKeyboardEnabled(false);
		other->removeFromParentAndCleanup(true);
		return;
	}

	// Basically PauseLayer::onPracticeEnd
	PlayLayer::get()->togglePracticeMode(false);
	PauseLayer_onResume(m_pLayer, false);
}