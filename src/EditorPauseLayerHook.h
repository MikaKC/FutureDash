#pragma once

#include "includes.h"

class EditorPauseLayerHook : public EditorPauseLayer
{
public:
	void onOptions(CCObject* pSender);
	static void LoadHooks();
};
