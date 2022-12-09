#pragma once
#include "includes.h"

class LevelCellHook : public gd::LevelCell
{
public:
    static void loadCustomLevelCell(gd::LevelCell* self);
    static void LoadHooks();
};