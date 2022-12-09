#pragma once

#include "includes.h"

class PauseLayerHook : public gd::PauseLayer 
{
public:
	static bool customSetup(gd::PauseLayer *self);
	static void onPracticeEnd(gd::PauseLayer *self, cocos2d::CCObject *pSender);
	static void LoadHooks();
	
	static gd::FLAlertLayer* createInfoLayer(gd::GJGameLevel* level);
	void onInfoLayer(cocos2d::CCObject* pSender);
	void onOptions(cocos2d::CCObject* pSender);
	void onHideUI(cocos2d::CCObject* pSender);
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
	static PracticeFLProtocol* create(gd::PauseLayer *lr);

	// Since hj's headers don't have this func, we add it ourselves - iAndyHD3 probably
	void PauseLayer_onResume(gd::PauseLayer *self, bool a2);

	void FLAlert_Clicked(gd::FLAlertLayer* other, bool btn2) override;
	
};