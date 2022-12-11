#pragma once

#include "includes.h"
#include "MenuLayerHook.hpp"

class PlayerInfoLayer : public FLAlertLayer
{
protected:
	int m_iCurrentIcon = 0;
	SimplePlayer* simplePlayerSprite;
	MenuLayerHook* m_pMenuLayer;

	int m_iCheckID = 0;
	IconType m_pCheckType = IconType::kIconTypeCube;
	CCSize m_pLrSize;

public:
	bool init(float _w, float _h, std::string title, MenuLayerHook* menulayer);
	void show() override;
	void setup();

	void onNextIcon(cocos2d::CCObject* pSender);
	void updateCheckIcon(cocos2d::CCObject* pSender);
	void onClose(cocos2d::CCObject* pSender);
	void keyBackClicked();
	
	void checkAndAnimate();
	void animateAndChangeIcon(int id, float desiredScale, IconType iconType);

	static PlayerInfoLayer* create(MenuLayerHook* menulayer);
	
	void onMoreInfoPressed(cocos2d::CCObject* pSender);
	inline std::string iconStringFromName(std::string const &icon, std::string const &colour, int const &id, bool const &addNewLine = true);
};