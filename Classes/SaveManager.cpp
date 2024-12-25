#include "SaveManager.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include <fstream>

USING_NS_CC;
using namespace rapidjson;


void SaveManager::saveResultToFile(const int level,const int score)
{
    std::string gamePath = FileUtils::getInstance()->getDefaultResourceRootPath();
    std::string filePath = gamePath + "leaderboard.json";

    std::string jsonString = FileUtils::getInstance()->getStringFromFile(filePath);

    Document jsonDoc;

    if (jsonString.empty())
    {
        jsonDoc.SetArray();
    }
    else
    {
        jsonDoc.Parse(jsonString.c_str());
        if (!jsonDoc.IsArray())
        {
            jsonDoc.SetArray();
        }
    }
    Document newEntry;
    newEntry.SetObject();
    newEntry.AddMember("Level", level, newEntry.GetAllocator());
    newEntry.AddMember("Score", score, newEntry.GetAllocator());

    jsonDoc.PushBack(newEntry, newEntry.GetAllocator());

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    jsonDoc.Accept(writer);
    
    FileUtils::getInstance()->writeStringToFile(buffer.GetString(), filePath);

}

std::vector<std::pair<const int,const int>> SaveManager::loadResultFromFile()
{
    std::string gamePath = FileUtils::getInstance()->getDefaultResourceRootPath();
    std::string filePath = gamePath + "leaderboard.json";

    std::string jsonString = FileUtils::getInstance()->getStringFromFile(filePath);
    Document jsonDoc;

    std::vector<std::pair<const int,const int>> results;

    if (!jsonString.empty())
    {
        jsonDoc.Parse(jsonString.c_str());
        if (jsonDoc.IsArray())
        {
            for (const auto& entry : jsonDoc.GetArray())
            {
                if (entry.HasMember("Level") && entry["Level"].IsInt() &&
                    entry.HasMember("Score") && entry["Score"].IsInt())
                {
                    results.emplace_back(entry["Level"].GetInt(), entry["Score"].GetInt());
                }
            }
        }
    }

    return results;
}

