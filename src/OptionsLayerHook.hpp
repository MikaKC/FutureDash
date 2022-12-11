#pragma once

#include "includes.h"

class OptionsLayerHook : public OptionsLayer
{
public:
	void customSetupHook();
	void musicSliderChangedHook();
	void optionsButtonPressedHook(CCObject* pSender);

	static void LoadHooks();
	void onCredits(cocos2d::CCObject*);
};