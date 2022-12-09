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
#define ALERT(TITLE, BTN1, BTN2, CONTENT) gd::FLAlertLayer::create(nullptr, TITLE, BTN1, BTN2, CONTENT)->show()

// MemberByOffset
#define MEMBERBYOFFSET(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)
#define MBO MEMBERBYOFFSET

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

static inline const char* getTextureName(cocos2d::CCSprite* sprite_node) {
	
	auto* texture = sprite_node->getTexture();
	cocos2d::CCDictElement* el;
		
	auto* frame_cache = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache();
	auto* cached_frames = public_cast(frame_cache, m_pSpriteFrames);
	const auto rect = sprite_node->getTextureRect();
	cocos2d::CCDICT_FOREACH(cached_frames, el) {
		auto* frame = static_cast<cocos2d::CCSpriteFrame*>(el->getObject());
		if (frame->getTexture() == texture && frame->getRect().equals(rect)) {
			return el->getStrKey();
		}
	}

	return "";
}