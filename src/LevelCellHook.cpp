#include "LevelCellHook.hpp"
#include "AbbreviatedLabels.hpp"

void LevelCellHook::loadCustomLevelCell(gd::LevelCell* self) {
	matdash::orig<&LevelCellHook::loadCustomLevelCell>(self);
	
	if(gd::GameManager::sharedState()->getGameVariable("2300")) return;
	
	auto layer = (CCLayer*)self->getChildren()->objectAtIndex(1);

	auto level = MBO(void*, self, 380);

	int likes = MBO(int, level, 624) - MBO(int, level, 628);
	int downloads = MBO(int, level, 488);
	

	bool checkDownload = downloads > 1000;
	bool checkLikes = likes > 1000;
	
	if(!checkDownload && !checkLikes)
		return;
	
	unsigned int count = layer->getChildrenCount();
	

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
}

void LevelCellHook::LoadHooks()
{
    matdash::add_hook<&LevelCellHook::loadCustomLevelCell>(gd::base + 0x5A020);
    std::cout << "Hooked LevelCell::loadCustomLevelCell" << std::endl;
}