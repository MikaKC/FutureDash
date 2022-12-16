#include "EditorPauseLayerHook.h"
#include "SelectMoreOptionsLayer.h"

void EditorPauseLayerHook::onOptions(CCObject* pSender)
{
	SelectMoreOptionsLayer::create()->show();
}

void EditorPauseLayerHook::LoadHooks()
{
	matdash::add_hook<&EditorPauseLayerHook::onOptions>(base + 0x74740);
	std::cout << "Hooked EditorPauseLayer::onOptions" << std::endl;
}