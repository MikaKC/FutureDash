#pragma once

#include "includes.h"

class PauseLayerHook : public gd::PauseLayer 
{
public:
    static bool customSetup(gd::PauseLayer *self);
    static void onPracticeEnd(gd::PauseLayer *self, cocos2d::CCObject *pSender);
    static void LoadHooks();
};

class PracticeFLProtocol : public gd::FLAlertLayerProtocol
{
protected:
    // lr
    gd::PauseLayer *m_pLayer;

public:

    PracticeFLProtocol(gd::PauseLayer *lr) { m_pLayer = lr; }
    ~PracticeFLProtocol() {}

    // wrapper for new PracticeFLProtocol();
    static PracticeFLProtocol* create(gd::PauseLayer *lr)
    {
        PracticeFLProtocol *pRet = new PracticeFLProtocol(lr);
        if (pRet)
        {
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }

    // Since hj's headers don't have this func, we add it ourselves - iAndyHD3 probably
    void PauseLayer_onResume(gd::PauseLayer *self, bool a2)
    {
        // needed __thiscall* not __fastcall*
        reinterpret_cast<void(__thiscall*)(gd::PauseLayer*, bool)>(
			gd::base + 0x1E5FA0
        )(self, a2);
    }

    void FLAlert_Clicked(gd::FLAlertLayer* other, bool btn2) override
    {
        if(!btn2) {
            other->setKeyboardEnabled(false);
            other->removeFromParentAndCleanup(true);
            return;
        }

        // Basically PauseLayer::onPracticeEnd
        gd::PlayLayer::get()->togglePracticeMode(false);
        PauseLayer_onResume(m_pLayer, false);
    }
};
