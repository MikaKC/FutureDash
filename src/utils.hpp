#pragma once

#include <MinHook.h>
#include <gd.h>

#define CREATE_HOOK(ADDRESS, HOOK, ORIGINAL) MH_CreateHook(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(GetModuleHandle(0)) + ADDRESS),reinterpret_cast<void*>(&HOOK),reinterpret_cast<void**>(&ORIGINAL));
#define ALERT(TITLE, BTN1, BTN2, CONTENT) gd::FLAlertLayer::create(nullptr, TITLE, BTN1, BTN2, CONTENT)->show();