#include "MoreOptionsLayerHook.hpp"

bool MoreOptionsLayerHook::init(MoreOptionsLayer* self)
{
	if(!matdash::orig<&MoreOptionsLayerHook::init>(self)) return false;

	// Still add this in case people want to disable it 
	self->addToggle("Disable\nabbreviated labels", "2300", "Disables the abbreviation on labels.");
	self->addToggle("Disable\n Icon", "11000", "Disables the abbreviation on labels.");

	return true;
}

void MoreOptionsLayerHook::LoadHooks()
{
	matdash::add_hook<&MoreOptionsLayerHook::init>(base + 0x1DE8F0);
	std::cout << "Hooked MoreOptionsLayer::init" << std::endl;
}
