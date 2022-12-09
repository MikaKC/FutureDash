#pragma once

#include "includes.h"

class OptionsLayerHook : public OptionsLayer
{
public:
	static void customSetup(OptionsLayer* self);
	static void musicSliderChanged(cocos2d::CCObject* pSender);
	static void LoadHooks();
	void onCredits(cocos2d::CCObject*);
};