#include "OptionsLayerHook.hpp"
#include "CreditsLayer.hpp"

void OptionsLayerHook::customSetup(gd::OptionsLayer* self)
{
	matdash::orig<&OptionsLayerHook::customSetup>(self);

	// layer is a member of gjdropdownlayer apparently!!!!
	auto layer = self->m_pLayer;
	unsigned int nodeCount = layer->getChildrenCount();

	auto creditsSpr = gd::ButtonSprite::create("Credits", 70, false, "goldFont.fnt", "GJ_button_01.png", 30, 1);
	auto creditsBtn = gd::CCMenuItemSpriteExtra::create(creditsSpr, self, (cocos2d::SEL_MenuHandler)&OptionsLayerHook::onCredits);
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
}

void OptionsLayerHook::onCredits(cocos2d::CCObject* pSender)
{
	CreditsLayer::create()->show();
}

// I guess its ccobject but i might be wrong
void OptionsLayerHook::musicSliderChanged(cocos2d::CCObject *a1)
{
	matdash::orig<&OptionsLayerHook::musicSliderChanged>(a1);
}

void OptionsLayerHook::LoadHooks()
{
	matdash::add_hook<&OptionsLayerHook::customSetup>(gd::base + 0x1DD420);
	std::cout << "Hooked OptionsLayer::customSetup" << std::endl;

	matdash::add_hook<&OptionsLayerHook::musicSliderChanged>(gd::base + 0x1DDE20);
	std::cout << "Hooked OptionsLayer::musicSliderChanged" << std::endl;
}