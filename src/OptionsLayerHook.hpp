#pragma once

#include "includes.h"

class OptionsLayerHook : public OptionsLayer
{
public:
	static void customSetup(OptionsLayer* self);
	static void musicSliderChanged(int* this_);
	static void LoadHooks();
	void onCredits(cocos2d::CCObject*);
};