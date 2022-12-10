#include "includes.h"

#include "LevelCellHook.hpp"
#include "LevelInfoLayerHook.hpp"
#include "ProfilePageHook.hpp"
#include "MoreOptionsLayerHook.hpp"
#include "OptionsLayerHook.hpp"
#include "PauseLayerHook.hpp"
#include "MenuLayerHook.hpp"

#include <matdash/boilerplate.hpp>

//0#define DEBUG

#ifdef DEBUG
	#include <matdash/console.hpp>
#endif

matdash::cc::thiscall<void> LoadingLayer_loadAssets(LoadingLayer* self)
{
  matdash::orig<&LoadingLayer_loadAssets>(self);

  // Useless

  return {};
}


void mod_main(HMODULE)
{
	#ifdef DEBUG
		if(AllocConsole())
		{
#pragma warning(push, 0)
			freopen("CONOUT$", "wt", stdout);
			freopen("CONIN$", "rt", stdin);
#pragma warning(pop)
			std::ios::sync_with_stdio(1);
		}
	#endif
	
	std::cout << "Loading hooks" << std::endl;

	// Hooks
	
	matdash::add_hook<&LoadingLayer_loadAssets>(base + 0x18C8E0);
	std::cout << "Hooked LoadingLayer::loadAssets" << std::endl;

	LevelInfoLayerHook::LoadHooks();
	MenuLayerHook::LoadHooks();
	PauseLayerHook::LoadHooks();
	OptionsLayerHook::LoadHooks();
	LevelCellHook::LoadHooks();
	MoreOptionsLayerHook::LoadHooks();
	ProfilePageHook::LoadHooks();


	std::cout << "Finished hooking" << std::endl;
}