#pragma once

#include "includes.h"

class MoreOptionsLayerHook : public MoreOptionsLayer
{
public:
	static bool init(MoreOptionsLayer* self);
	static void LoadHooks();
};