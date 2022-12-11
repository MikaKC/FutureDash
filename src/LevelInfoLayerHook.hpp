#pragma once

#include "includes.h"

class LevelInfoLayerHook : public LevelInfoLayer
{
public:
	bool initHook(GJGameLevel* level);
	void updateLabelValuesHook();
	static void LoadHooks();
	void onLevelBadgeInfo(cocos2d::CCObject* pSender);
	void onMoreOptionsLayerButtonPressed(cocos2d::CCObject* pSender);
};