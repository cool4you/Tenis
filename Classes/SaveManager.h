#pragma once
#include "cocos2d.h"

class SaveManager
{
public:
	static void saveResultToFile(int level, int score);
	static std::vector<std::pair<int, int>> loadResultFromFile();
};