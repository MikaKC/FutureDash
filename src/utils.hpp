#pragma once

#include <gd.h>

/*FLAlertLayer supports colors of text for the caption. wrap desired text in "<cx></c>"
	* where x is the color desired. colors are:
	* r - red
	* l - lime
	* g - green
	* y - yellow
	* o - orange
*/
#define ALERT(TITLE, BTN1, BTN2, CONTENT) FLAlertLayer::create(nullptr, TITLE, BTN1, BTN2, CONTENT)->show()

//i find this a lot more elegant
#define GM GameManager::sharedState()
#define DIR cocos2d::CCDirector::sharedDirector()

// MemberByOffset
#define MEMBERBYOFFSET(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)
#define MBO MEMBERBYOFFSET