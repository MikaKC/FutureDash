#pragma once

#include "includes.h"

struct AbbreviatedLabels{
	inline static const std::string thousandSeparator(int n)
	{
		using namespace std;
		string ans = "";
	
		// Convert the given integer
		// to equivalent string
		string num = std::to_string(n);
	
		// Initialise count
		int count = 0;
	
		// Traverse the string in reverse
		for (int i = num.size() - 1;
			i >= 0; i--) {
			count++;
			ans.push_back(num[i]);
	
			// If three characters
			// are traversed
			if (count == 3) {
				ans.push_back('.');
				count = 0;
			}
		}
	
		// Reverse the string to get
		// the desired output
		reverse(ans.begin(), ans.end());
	
		// If the given string is
		// less than 1000
		if (ans.size() % 4 == 0) {
	
			// Remove ','
			ans.erase(ans.begin());
		}
	
		return ans;
	}
	inline static const std::string intToFormattedString(int n, float& scaleMult) 
	{
		
		
		if(n < 1000 || n > 100000000)
		return std::to_string(n);

		std::string str = thousandSeparator(n);
		str = str.substr(0, str.find(".") + 2);

		char sufix;

		if(n < 1000000) { sufix = 'K'; scaleMult = 1.1f; }
		else if(n < 100000000) { sufix = 'M'; scaleMult = 1.5f; }
		
		
		return str += sufix ;
	}
	inline static bool isNumber(const char* str)
	{
		std::string s(str);
		return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
	}
	
	struct ScaleParams : public CCObject {
		float oldScale;
		float newscale;
		
		ScaleParams(float o, float n) : oldScale(o), newscale(n) {
			this->autorelease();
		}
	};
	
	struct Callbacks 
	{
		void onLabel(CCNode* sender)
		{
			auto label = (CCLabelBMFont*)sender->getChildren()->objectAtIndex(0);
			int n = sender->getTag();
			auto scales = static_cast<AbbreviatedLabels::ScaleParams*>(sender->getUserObject());
			
			auto labelstr = label->getString();
			if(AbbreviatedLabels::isNumber(labelstr))
			{
				float scaleMult = 1.0f;
				label->CCLabelBMFont::setString(AbbreviatedLabels::intToFormattedString(n, scaleMult).c_str());
				label->setScale(scales->newscale);
			}
			else
			{
				label->CCLabelBMFont::setString(std::to_string(n).c_str());
				label->setScale(scales->oldScale);
			}
		}
	};
};