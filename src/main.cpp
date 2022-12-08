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


// MemberByOffset
#define MEMBERBYOFFSET(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)
#define MBO MEMBERBYOFFSET

struct AbbreviatedLabels{
    inline static const std::string thousandSeparator(int n)
    {
        using namespace std;
        string ans = "";
    
        // Convert the given integer
        // to equivalent string
        string num = std::to_string(n);
    
        // Initialise count
        int count = 0;
    
        // Traverse the string in reverse
        for (int i = num.size() - 1;
            i >= 0; i--) {
            count++;
            ans.push_back(num[i]);
    
            // If three characters
            // are traversed
            if (count == 3) {
                ans.push_back('.');
                count = 0;
            }
        }
    
        // Reverse the string to get
        // the desired output
        reverse(ans.begin(), ans.end());
    
        // If the given string is
        // less than 1000
        if (ans.size() % 4 == 0) {
    
            // Remove ','
            ans.erase(ans.begin());
        }
    
        return ans;
    }
    inline static const std::string intToFormattedString(int n, float& scaleMult) 
    {
        
        
        if(n < 1000 || n > 100000000)
        return std::to_string(n);

        std::string str = thousandSeparator(n);
        str = str.substr(0, str.find(".") + 2);

        char sufix;

        if(n < 1000000) { sufix = 'K'; scaleMult = 1.1f; }
        else if(n < 100000000) { sufix = 'M'; scaleMult = 1.5f; }
        
        
        return str += sufix ;
    }
    inline static bool isNumber(const char* str)
    {
        std::string s(str);
        return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    }
    
    struct ScaleParams : public CCObject {
        float oldScale;
        float newscale;
        
        ScaleParams(float o, float n) : oldScale(o), newscale(n) {
            this->autorelease();
        }
    };
    struct Callbacks 
    {
        void onLabel(CCNode* sender)
        {
            auto label = (CCLabelBMFont*)sender->getChildren()->objectAtIndex(0);
            int n = sender->getTag();
            auto scales = static_cast<AbbreviatedLabels::ScaleParams*>(sender->getUserObject());
            
            auto labelstr = label->getString();
            if(AbbreviatedLabels::isNumber(labelstr))
            {
                float scaleMult = 1.0f;
                label->CCLabelBMFont::setString(AbbreviatedLabels::intToFormattedString(n, scaleMult).c_str());
                label->setScale(scales->newscale);
            }
            else
            {
                label->CCLabelBMFont::setString(std::to_string(n).c_str());
                label->setScale(scales->oldScale);
            }
        }
    };
};

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

  // Useless

  return {};
}

bool PauseLayer_customSetup(gd::PauseLayer* self)
{
    if(!matdash::orig<&PauseLayer_customSetup>(self)) return false;

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    // self->setTag(696969);

    int nodeCount = self->getChildrenCount();

    // This shit doesn't work (need to get the GJGameLevel idk how, but its possible since the title is displayed)
    auto infoButton = gd::CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png"), self, menu_selector(Callbacks::onPauseLayerInfoPressed));
    infoButton->setScale(1.3f);
    infoButton->m_fBaseScale = 1.3f;
    infoButton->setPositionX(-209.f);

    auto settingsBtn = gd::CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"), self, reinterpret_cast<SEL_MenuHandler>(&Callbacks::onOptionsLayerButtonPressed));
    settingsBtn->setPosition({winSize.width / 2 - 85, winSize.height / 2 - 20});

    auto hideUIMenu = CCMenu::create();
    self->addChild(hideUIMenu, 11);

    // Ill change it to something more consistent but I just want to push my changes
    hideUIMenu->setPosition({460.5f, 270});

    // This shit doesn't work (i need to get player input through CCTouchDispatcher but idk how)
    auto hideUIButton = gd::CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"), self, reinterpret_cast<SEL_MenuHandler>(&Callbacks::hidePauseLayerUI));
    hideUIMenu->addChild(hideUIButton);
    
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
                    std::cout << "Playtest\n";
                    menu->setPositionX(284.5f);
                    // repositionner
                    settingsBtn->setPositionX(winSize.width / 2 - 49.5f);
                    
                    infoButton->setVisible(false);
                } 
                else {
                    std::cout << "Game\n";
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

matdash::cc::thiscall<void> LevelInfoLayer_updateLabelValues(gd::LevelInfoLayer* self)
{
    matdash::orig<&LevelInfoLayer_updateLabelValues>(self);

    CCObject* node;

    // Fixes the weird bug type beat
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

    return {};
}

matdash::cc::thiscall<void> OptionsLayer_customSetup(gd::OptionsLayer* self)
{
    matdash::orig<&OptionsLayer_customSetup>(self);

    // layer is a member of gjdropdownlayer apparently!!!!
    auto layer = self->m_pLayer;
    unsigned int nodeCount = layer->getChildrenCount();

    auto creditsSpr = gd::ButtonSprite::create("Credits", 70, false, "goldFont.fnt", "GJ_button_01.png", 30, 1);
    auto creditsBtn = gd::CCMenuItemSpriteExtra::create(creditsSpr, self, reinterpret_cast<SEL_MenuHandler>(&Callbacks::onCreditsButtonPressed));
    creditsBtn->setPositionY(80);

    for (unsigned int i = 0; i < nodeCount; i++)
    {
        auto nodes = reinterpret_cast<CCNode*>(layer->getChildren()->objectAtIndex(i));

        if(auto menu = dynamic_cast<CCMenu*>(nodes))
        {
            if(menu->getChildrenCount() > 1)
            {
                auto btn1 = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(menu->getChildren()->objectAtIndex(0));
                auto btn2 = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(menu->getChildren()->objectAtIndex(1));
                auto btn3 = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(menu->getChildren()->objectAtIndex(2));
                auto btn4 = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(menu->getChildren()->objectAtIndex(3));
                
                auto btn1spr = reinterpret_cast<gd::ButtonSprite*>(btn1->getChildren()->objectAtIndex(0));
                auto btn2spr = reinterpret_cast<gd::ButtonSprite*>(btn2->getChildren()->objectAtIndex(0));
                auto btn3spr = reinterpret_cast<gd::ButtonSprite*>(btn3->getChildren()->objectAtIndex(0));
                auto btn4spr = reinterpret_cast<gd::ButtonSprite*>(btn4->getChildren()->objectAtIndex(0));

                btn1->setPosition({-107, 80});
                btn1->setContentSize({94, 30});
                btn1spr->setPosition({49, 15});
                btn1spr->m_pBGSprite->setPosition({73, 15});
                btn1spr->m_pBGSprite->setContentSize({94, 30});
                btn1spr->m_pLabel->setPosition({73, 17});
                btn1spr->m_pLabel->setScale(0.775f);

                btn2->setPosition({102, 80});
                btn2->setContentSize({94, 30});
                btn2spr->setPosition({50, 15});
                btn2spr->m_pBGSprite->setPosition({73, 15});
                btn2spr->m_pBGSprite->setContentSize({94, 30});
                btn2spr->m_pLabel->setPosition({73, 17});
                btn2spr->m_pLabel->setScale(0.512f);
                
                menu->addChild(creditsBtn);
            }
        }
    }

    return {};
}

bool MoreOptionsLayer_init(gd::MoreOptionsLayer* self)
{
    if(!matdash::orig<&MoreOptionsLayer_init>(self)) return false;

    // Still add this in case people want to disable it 
    self->addToggle("Disable abbreviated labels", "2300", "Disables the abbreviation on labels.");

    return true;
}

// Thanks again to iAndy_HD3
matdash::cc::thiscall<void> LevelCell_loadCustomLevelCell(gd::LevelCell* self) {
	matdash::orig<&LevelCell_loadCustomLevelCell>(self);

	auto layer = (CCLayer*)self->getChildren()->objectAtIndex(1);

	auto level = MBO(void*, self, 380);

	int likes = MBO(int, level, 624) - MBO(int, level, 628);
	int downloads = MBO(int, level, 488);
	

	bool checkDownload = downloads > 1000;
	bool checkLikes = likes > 1000;
	
	if(!checkDownload && !checkLikes)
		return {};
	
	unsigned int count = layer->getChildrenCount();
	
    if(!gd::GameManager::sharedState()->getGameVariable("2300"))
    {
        for(unsigned int i = 0; i < count; i++)
        {
            auto node = (CCNode*)layer->getChildren()->objectAtIndex(i);

            if(auto label = dynamic_cast<CCLabelBMFont*>(node))
            {
                if(checkDownload && atoi(label->CCLabelBMFont::getString()) == downloads)
                {
                    float scaleMult = 1.0f;
                    auto newspr = CCLabelBMFont::create(AbbreviatedLabels::intToFormattedString(downloads, scaleMult).c_str(), "bigFont.fnt");
                    float oldScale = label->getScale();
                    float newscale = oldScale * scaleMult;
                    newspr->setScale(newscale);

                    auto btn = gd::CCMenuItemSpriteExtra::create(newspr, self, menu_selector(AbbreviatedLabels::Callbacks::onLabel));
                    btn->setTag(downloads);
                    btn->setUserObject(new AbbreviatedLabels::ScaleParams(oldScale, newscale));
                    
                    auto menu = CCMenu::create();
                    menu->setPosition(label->getPosition());
                    menu->setPositionX(menu->getPositionX() + 20);
                    menu->addChild(btn);
                    self->addChild(menu);
                    label->setVisible(false);
                    
                    continue;
                }
                else if(checkLikes && atoi(label->CCLabelBMFont::getString()) == likes)
                {
                    float scaleMult = 1.0f;
                    auto newspr = CCLabelBMFont::create(AbbreviatedLabels::intToFormattedString(likes, scaleMult).c_str(), "bigFont.fnt");
                    float oldScale = label->getScale();
                    float newscale = oldScale * scaleMult;
                    newspr->setScale(newscale);

                    auto btn = gd::CCMenuItemSpriteExtra::create(newspr, self, menu_selector(AbbreviatedLabels::Callbacks::onLabel));
                    btn->setTag(likes);
                    btn->setUserObject(new AbbreviatedLabels::ScaleParams(oldScale, newscale));
                    
                    auto menu = CCMenu::create();
                    menu->setPosition(label->getPosition());
                    menu->setPositionX(menu->getPositionX() + 20);
                    menu->addChild(btn);
                    self->addChild(menu);
                    label->setVisible(false);
                    
                }
            }
        }
    } else {
        return {};
    }

    return {};
}

matdash::cc::thiscall<void> ProfilePage_loadPageWithUserInfo(gd::ProfilePage *self, gd::GJUserScore *score)
{
    matdash::orig<&ProfilePage_loadPageWithUserInfo>(self, score);

    auto layer = reinterpret_cast<CCLayer*>(self->getChildren()->objectAtIndex(0));
	
    auto menu = CCMenu::create();
    menu->setPosition({0, 0});
    layer->addChild(menu);

    for(unsigned int i = 0; i < layer->getChildrenCount(); i++)
	{
		CCObject* o = layer->getChildren()->objectAtIndex(i);	
		if(auto s = dynamic_cast<CCSprite*>(o)) 
		{
			
			auto tname = getTextureName(s);
			std::cout << i << ' ' << tname << std::endl;
			
			int num = 0;
			if(strcmp(tname, "modBadge_01_001.png") == 0) num = 1;
			else if(strcmp(tname, "modBadge_02_001.png") == 0) num = 2;
			
			if(num != 0)
			{
				auto newspr = CCSprite::createWithSpriteFrameName(tname);
				newspr->setScale(s->getScale());
				auto btn = gd::CCMenuItemSpriteExtra::create(newspr, self, menu_selector(Callbacks::onModeratorBadgeInfo));
				btn->setTag(num);
                btn->setPosition(s->getPosition());
                menu->addChild(btn);
                s->setVisible(false);
			}
		}
	}

    return {};
}

// I guess its ccobject but i might be wrong
matdash::cc::thiscall<void> OptionsLayer_musicSliderChanged(cocos2d::CCObject *a1)
{
    matdash::orig<&OptionsLayer_musicSliderChanged>(a1);

    // auto *musicLevel = MBO(double*, a1, 84);
    // std::cout << musicLevel << std::endl;

    return {};
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
	
    std::cout << "Loading hooks" << std::endl;

    // Hooks
    matdash::add_hook<&LevelInfoLayer_init>(gd::base + 0x175DF0);
    std::cout << "Hooked LevelInfoLayer::init" << std::endl;

    // LevelInfoLayer_updateLabels
    matdash::add_hook<&LevelInfoLayer_updateLabelValues>(gd::base + 0x17B170);
    std::cout << "Hooked LevelInfoLayer::updateLabelValues" << std::endl;

    matdash::add_hook<&MenuLayer_init>(gd::base + 0x1907B0);
    std::cout << "Hooked MenuLayer::init" << std::endl;

    matdash::add_hook<&PauseLayer_customSetup>(gd::base + 0x1E4620);
    std::cout << "Hooked PauseLayer::customSetup" << std::endl;
    
    matdash::add_hook<&LoadingLayer_loadAssets>(gd::base + 0x18C8E0);
    std::cout << "Hooked LoadingLayer::loadAssets" << std::endl;

    matdash::add_hook<&OptionsLayer_customSetup>(gd::base + 0x1DD420);
    std::cout << "Hooked OptionsLayer::customSetup" << std::endl;

    matdash::add_hook<&LevelCell_loadCustomLevelCell>(gd::base + 0x5A020);
    std::cout << "Hooked LevelCell::loadCustomLevelCell" << std::endl;

    matdash::add_hook<&MoreOptionsLayer_init>(gd::base + 0x1DE8F0);
    std::cout << "Hooked MoreOptionsLayer::init" << std::endl;

    matdash::add_hook<&OptionsLayer_musicSliderChanged>(gd::base + 0x1DDE20);
    std::cout << "Hooked OptionsLayer::musicSliderChanged" << std::endl;

    matdash::add_hook<&ProfilePage_loadPageWithUserInfo>(gd::base + 0x210040);
    std::cout << "Hooked ProfilePage::loadWithUserInfo" << std::endl;

    std::cout << "Finished hooking" << std::endl;
}