#pragma once

#include "includes.h"

class ProfilePageHook : gd::ProfilePage
{
public:
    static void loadPageWithUserInfo(gd::ProfilePage* self, gd::GJUserScore *score);
    static void LoadHooks();
};