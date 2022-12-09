#pragma once

#include "includes.h"

class LevelInfoLayerHook : public LevelInfoLayer
{
public:
	static bool init(LevelInfoLayer* self, GJGameLevel* level);
	static void updateLabelValues(LevelInfoLayer* self);
	static void LoadHooks();
	void onLevelBadgeInfo(cocos2d::CCObject* pSender);
	void onMoreOptionsLayerButtonPressed(cocos2d::CCObject* pSender);
};