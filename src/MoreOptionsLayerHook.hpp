#pragma once

#include "includes.h"

class MoreOptionsLayerHook : public gd::MoreOptionsLayer
{
public:
	static bool init(gd::MoreOptionsLayer* self);
	static void LoadHooks();
};