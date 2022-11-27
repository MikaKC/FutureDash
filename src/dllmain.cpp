#include "includes.h"

bool (__thiscall* MenuLayer_init)(gd::MenuLayer* self);
bool __fastcall MenuLayer_init_H(gd::MenuLayer* self, void*) {

    if (!MenuLayer_init(self)) return false;

    auto infoButton = gd::CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
        self,
        menu_selector(Callbacks::onInfoButtonPressed)
    );

    infoButton->setScale(0.75f);
    infoButton->m_fBaseScale = 0.75f;
    infoButton->m_fScaleMultiplier = 1.25f;

    auto menu = CCMenu::create();
    menu->addChild(infoButton);
    menu->setPosition({83, 123});

    self->addChild(menu);

    return true;
}

void (__thiscall* LoadingLayer_loadAssets)(gd::LoadingLayer* self);
void __fastcall LoadingLayer_loadAssets_H(gd::LoadingLayer* self, void *)
{
  LoadingLayer_loadAssets(self);

  // Load sprite sheets n stuff
}

DWORD WINAPI thread_func(void* hModule) {

    MH_Initialize();

    auto base = gd::base;
    
    CREATE_HOOK(0x1907b0, MenuLayer_init_H, MenuLayer_init);
    CREATE_HOOK(0x18c8e0, LoadingLayer_loadAssets_H, LoadingLayer_loadAssets);

    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}


// Win32 boilerplate
BOOL APIENTRY DllMain(HMODULE handle, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        auto h = CreateThread(0, 0, thread_func, handle, 0, 0);
        if (h)
            CloseHandle(h);
        else
            return FALSE;
    }
    return TRUE;
}