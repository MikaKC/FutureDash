#pragma once
#include "includes.h"

class MenuLayerHook : public MenuLayer
{
public:

SimplePlayer* m_pProfileIconSprite;

public:
	bool init_();
	static void LoadHooks();
	void onPlayerInfo(cocos2d::CCObject* pSender);
	void replaceAccountButton();
};