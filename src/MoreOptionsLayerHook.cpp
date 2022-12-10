#include "MoreOptionsLayerHook.hpp"

bool MoreOptionsLayerHook::init(MoreOptionsLayer* self)
{
	if(!matdash::orig<&MoreOptionsLayerHook::init>(self)) return false;

	// I don't really like the line skip so I just removed it, if you wan't you can add it back
	// self->addToggle("Disable\nabbreviated labels", "2300", "Disables the abbreviation on labels.");
	// self->addToggle("Disable\n Icon", "11000", "Reverts to the original icon on the menu.");

	self->addToggle("Disable abbreviated labels", "2300", "Disables the abbreviation on labels.");
	self->addToggle("Disable Icon", "2301", "Reverts icon button to the original button on the menu.");
	self->addToggle("Disables Practice Popup", "2302", "Disables the exit practice mode pop-up.");

	return true;
}

void MoreOptionsLayerHook::LoadHooks()
{
	matdash::add_hook<&MoreOptionsLayerHook::init>(base + 0x1DE8F0);
	std::cout << "Hooked MoreOptionsLayer::init" << std::endl;
}
