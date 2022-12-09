#pragma once

#include "includes.h"

class ProfilePageHook : ProfilePage
{
public:
	static void loadPageWithUserInfo(ProfilePage* self, GJUserScore *score);
	static void LoadHooks();
	void onModeratorBadgeInfo(cocos2d::CCObject* pSender);
};