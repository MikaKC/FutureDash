#pragma once

#include "includes.h"

class CreditsLayer : public gd::FLAlertLayer
{
protected:
	void onIconClicked(cocos2d::CCObject* pSender);
	cocos2d::CCSize m_pLrSize;

public:
	bool init(float _w, float _h, std::string title);
	void setup();

	void onClose(cocos2d::CCObject *pSnder);

	static CreditsLayer* create();
};