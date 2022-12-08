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
#define ALERT(TITLE, BTN1, BTN2, CONTENT) gd::FLAlertLayer::create(nullptr, TITLE, BTN1, BTN2, CONTENT)->show()

#define public_cast(value, member) [](auto* v) { \
	class FriendClass__; \
	using T = std::remove_pointer<decltype(v)>::type; \
	class FriendeeClass__: public T { \
	protected: \
		friend FriendClass__; \
	}; \
	class FriendClass__ { \
	public: \
		auto& get(FriendeeClass__* v) { return v->member; } \
	} c; \
	return c.get(reinterpret_cast<FriendeeClass__*>(v)); \
}(value)