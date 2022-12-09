#pragma once

#include "includes.h"

class LevelInfoLayerHook : public gd::LevelInfoLayer
{
public:
    static bool init(gd::LevelInfoLayer* self, gd::GJGameLevel* level);
    static void updateLabelValues(gd::LevelInfoLayer* self);
    static void LoadHooks();
};