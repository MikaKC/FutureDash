#pragma once

#include "includes.h"

class MoreOptionsLayerHook : public MoreOptionsLayer
{
public:
	bool initHook();
	static void LoadHooks();
};