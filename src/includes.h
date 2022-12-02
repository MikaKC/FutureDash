#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma warning(push, 0)
#include <cocos2d.h>
#pragma warning(pop)
#include <MinHook.h>
#include <gd.h>
#include "utils.hpp"
#include "Callbacks.hpp"
#include <format>
#include <iostream>

using std::uintptr_t;

using namespace cocos2d;
