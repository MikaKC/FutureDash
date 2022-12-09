#pragma once

#include "includes.h"

class OptionsLayerHook : public gd::OptionsLayer
{
public:
	static void customSetup(gd::OptionsLayer* self);
	static void musicSliderChanged(cocos2d::CCObject* pSender);
	static void LoadHooks();
	void onCredits(cocos2d::CCObject*);
};