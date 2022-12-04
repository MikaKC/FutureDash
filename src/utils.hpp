#pragma once

#include <MinHook.h>
#include <gd.h>

/*FLAlertLayer supports colors of text for the caption. wrap desired text in "<cx></c>"
	* where x is the color desired. colors are:
	* r - red
	* l - lime
	* g - green
	* y - yellow
	* o - orange
*/
#define ALERT(TITLE, BTN1, BTN2, CONTENT) gd::FLAlertLayer::create(nullptr, TITLE, BTN1, BTN2, CONTENT)->show();