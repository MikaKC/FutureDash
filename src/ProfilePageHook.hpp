#pragma once

#include "includes.h"

class ProfilePageHook : ProfilePage
{
public:
	void loadPageWithUserInfoHook(GJUserScore *score);
	static void LoadHooks();
	void onModeratorBadgeInfo(cocos2d::CCObject* pSender);
};