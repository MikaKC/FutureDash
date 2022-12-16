#include "PauseLayerHook.hpp"

bool PauseLayerHook::customSetupHook()
{
	if(!matdash::orig<&PauseLayerHook::customSetupHook>(this)) return false;

	CCDirector *dir = CCDirector::sharedDirector();
	
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	int nodeCount = this->getChildrenCount();

	auto pauseBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"), this, (SEL_MenuHandler)(&PauseLayerHook::onOptions));
	pauseBtn->setScale(0.85f);
	pauseBtn->m_fBaseScale = 0.85f;
	
	auto m = CCMenu::create();
	m->setPosition(40, winSize.height - 40);
	m->addChild(pauseBtn);
	this->addChild(m);
	
	auto hideUIMenu = CCMenu::create();
	this->addChild(hideUIMenu, 11);

	hideUIMenu->setPosition({winSize.width - 40, winSize.height - 40});

	auto hideUIButton = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"), this, (SEL_MenuHandler)(&PauseLayerHook::onHideUI));
	hideUIButton->setUserObject(this);
	hideUIMenu->addChild(hideUIButton);

	std::string creatorNameString = ((PlayLayer::get()->m_level->m_sCreatorName == "") ? "RobTopGames" : PlayLayer::get()->m_level->m_sCreatorName);
	auto authorText = CCLabelBMFont::create(std::format("By {}", creatorNameString).c_str(), "goldFont.fnt");
	this->addChild(authorText, 11);
	// change by the left
	authorText->setAlignment(CCTextAlignment::kCCTextAlignmentLeft);
	authorText->setPosition({winSize.width / 2, winSize.height - 60});

	const auto blueSlider = ccc3(0, 255, 255);

	bool isEditorLevel = MBO(int, MBO(void*, MBO(void*, GM, 356), 1160), 868) == 2;

	auto slidersMenu = CCMenu::create();
	this->addChild(slidersMenu, 3);
	slidersMenu->setPosition({0, 0});

	for (int i = 0; i < nodeCount; i++)
	{
		auto nodes = reinterpret_cast<CCNode*>(this->getChildren()->objectAtIndex(i));
		
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

					menu->setPositionY(menu->getPositionY() + 37.5f);

					std::cout << j << ' ' << tname << std::endl;

					if (isEditorLevel) break;
					else if(strcmp(tname, "GJ_playBtn2_001.png") == 0)
					{
						auto infoButton = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png"), this, (SEL_MenuHandler)(&PauseLayerHook::onInfoLayer));
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
		else if(auto label = dynamic_cast<CCLabelBMFont*>(nodes))
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
			else if(strcmp(label->getString(), std::format("{}%", PlayLayer::get()->m_level->m_nPracticePercent).c_str()) == 0)
			{
				label->setVisible(false);
			}
			else if(strcmp(label->getString(), std::format("{}%", PlayLayer::get()->m_level->m_nNormalPercent).c_str()) == 0)
			{
				label->setVisible(false);
			}
			else if(strcmp(label->getString(), "Normal Mode") == 0)
			{
				label->setVisible(false);
			}
			else if(strcmp(label->getString(), "Practice Mode") == 0)
			{
				label->setVisible(false);
			}
		}
		else if(auto slider = dynamic_cast<CCLayer*>(nodes))
		{
			if (slider->getChildrenCount() < 3)
			{
				slider->setVisible(false);
			}
		}
		else if(auto sprite = dynamic_cast<CCSprite*>(nodes))
		{
			const char* tname = ModToolbox::getTextureNameForSprite(sprite);
			std::string tnamestr = std::string(tname);

			std::cout << i << ' ' << tname << std::endl;

			bool condTname = (tnamestr.find("GJ_progressBar_001-uhd.png") != std::string::npos) 
				|| (tnamestr.find("GJ_progressBar_001-hd.png") != std::string::npos) 
				|| (tnamestr.find("GJ_progressBar_001.png") != std::string::npos);

			if(condTname)
			{
				auto otherObj = reinterpret_cast<CCSprite*>(sprite->getChildren()->objectAtIndex(0));

				std::cout << "progressbar" << std::endl;

				if (otherObj->getColor().r == blueSlider.r
					&& otherObj->getColor().g == blueSlider.g
					&& otherObj->getColor().b == blueSlider.b)
				{
					std::cout << "practicebar" << std::endl;
					
					sprite->setPosition(ccp(sprite->getPosition().x, sprite->getPosition().y - 70));

					auto practicePercentLabel = CCLabelBMFont::create(std::format("{}%", PlayLayer::get()->m_level->m_nPracticePercent).c_str(), "bigFont.fnt");
					practicePercentLabel->setPosition(ccp(sprite->getPosition().x, sprite->getPosition().y));
					practicePercentLabel->setScale(0.5f);
					this->addChild(practicePercentLabel, 10);
					
					auto practiceTextLabel = CCLabelBMFont::create("Practice Mode", "bigFont.fnt");
					practiceTextLabel->setScale(0.5f);
					this->addChild(practiceTextLabel, 10);
					practiceTextLabel->setPosition(ccp(sprite->getPosition().x, sprite->getPositionY() + practiceTextLabel->getContentSize().height - 10));

				}
				else {
					std::cout << "normalbar" << std::endl;

					sprite->setPosition(ccp(sprite->getPosition().x, sprite->getPosition().y - 170));

					auto normalPercentLabel = CCLabelBMFont::create(std::format("{}%", PlayLayer::get()->m_level->m_nNormalPercent).c_str(), "bigFont.fnt");
					normalPercentLabel->setPosition(ccp(sprite->getPosition().x, sprite->getPosition().y));
					normalPercentLabel->setScale(0.5f);
					this->addChild(normalPercentLabel, 10);

					auto normalTextLabel = CCLabelBMFont::create("Normal Mode", "bigFont.fnt");
					normalTextLabel->setScale(0.5f);
					this->addChild(normalTextLabel, 10);
					normalTextLabel->setPosition(ccp(sprite->getPosition().x, sprite->getPositionY() + normalTextLabel->getContentSize().height - 10));

				}

				std::cout << "end" << std::endl;
			}
		}
	}

	return true;
}

void PauseLayerHook::onPracticeEndHook(cocos2d::CCObject *pSender)
{
	if(!GM->getGameVariable("2302"))
	{
		auto protocol = PracticeFLProtocol::create(this);
		FLAlertLayer::create(protocol, "Exit", "NO", "YES", "<cr>Exit</c> practice mode?")->show();
	} else {
		matdash::orig<&PauseLayerHook::onPracticeEndHook>(this, pSender);
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
	matdash::add_hook<&PauseLayerHook::customSetupHook>(base + 0x1E4620);
	std::cout << "Hooked PauseLayer::customSetup" << std::endl;

	matdash::add_hook<&PauseLayerHook::onPracticeEndHook>(base + 0x1E5F60);
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

//PracticeFLProtocol (do you want to exit)
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
	reinterpret_cast<void(__thiscall*)(PauseLayer*, bool)>(
		base + 0x1E5FA0
	)(self, a2);
}

void PracticeFLProtocol::FLAlert_Clicked(FLAlertLayer* other, bool btn2)
{
	if (!btn2)
	{
		other->setKeyboardEnabled(false);
		other->removeFromParentAndCleanup(true);
		return;
	}

	PlayLayer::get()->togglePracticeMode(false);
	PauseLayer_onResume(m_pLayer, false);
}