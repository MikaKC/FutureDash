#pragma once

#include "includes.h"

class PauseLayerHook : public PauseLayer 
{
public:
	bool customSetupHook();
	void onPracticeEndHook(cocos2d::CCObject *pSender);
	static void LoadHooks();
	
	static FLAlertLayer* createInfoLayer(GJGameLevel* level);
	void onInfoLayer(cocos2d::CCObject* pSender);
	void onOptions(cocos2d::CCObject* pSender);
	void onHideUI(cocos2d::CCObject* pSender);
};

class PracticeFLProtocol : public FLAlertLayerProtocol
{
protected:
	// lr
	PauseLayer *m_pLayer;

public:

	PracticeFLProtocol(PauseLayer *lr) { m_pLayer = lr; }
	~PracticeFLProtocol() {}

	// wrapper for new PracticeFLProtocol();
	static PracticeFLProtocol* create(PauseLayer *lr);

	// Since hj's headers don't have this func, we add it ourselves - iAndyHD3 probably
	void PauseLayer_onResume(PauseLayer *self, bool a2);

	void FLAlert_Clicked(FLAlertLayer* other, bool btn2) override;
	
};