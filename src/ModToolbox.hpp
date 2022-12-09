#pragma once

#include "includes.h"

//general purpose class for helper functions that can be useful with any class at any moment
//(robtop - GameToolbox)

namespace ModToolbox
{
	const char* getTextureName(cocos2d::CCSprite* sprite_node);
	int frameForIcon(IconType icon);
};
