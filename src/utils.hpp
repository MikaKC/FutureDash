#pragma once

#include <MinHook.h>
#include <gd.h>

/*Registers a hook to a function
    @param ADDRESS: The address to the function to hook
    @param HOOK: The detour to the function
    @param ORIGINAL: The original function
*/
#define CREATE_HOOK(ADDRESS, HOOK, ORIGINAL) MH_CreateHook(reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(GetModuleHandle(0)) + ADDRESS),reinterpret_cast<void*>(&HOOK),reinterpret_cast<void**>(&ORIGINAL));

/*FLAlertLayer supports colors of text for the caption. wrap desired text in "<cx></c>"
	* where x is the color desired. colors are:
	* r - red
	* l - lime
	* g - green
	* y - yellow
	* o - orange
*/
#define ALERT(TITLE, BTN1, BTN2, CONTENT) gd::FLAlertLayer::create(nullptr, TITLE, BTN1, BTN2, CONTENT)->show();