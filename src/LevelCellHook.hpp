#pragma once
#include "includes.h"

class LevelCellHook : public LevelCell
{
public:
	static void loadCustomLevelCell(LevelCell* self);
	static void LoadHooks();
};