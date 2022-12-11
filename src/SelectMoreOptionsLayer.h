#pragma once

#include "includes.h"

class SelectMoreOptionsLayer : public FLAlertLayer
{
private:
	CCSize m_pLrSize;
public:
	bool init(float _x, float _y, std::string title);
	void setup();

	void onClose(CCObject* pSender);
	void onSelectorButtonPressed(CCObject* pSender);

	static SelectMoreOptionsLayer* create();
};

