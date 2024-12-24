#pragma once
#include "cocos2d.h"

class SaveManager
{
public:
	static void saveResultToFile(const int level,const int score);
	static std::vector<std::pair<const int,const int>> loadResultFromFile();
};