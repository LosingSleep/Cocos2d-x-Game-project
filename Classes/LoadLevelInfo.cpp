//
//  LoadLevelInfo.cpp
//  NoOneSurvival
//
//  Created by 陈晖 on 16/6/9.
//
//

#include "LoadLevelInfo.hpp"
#include "GameManager.hpp"

USING_NS_CC;


LoadLevelinfo::~LoadLevelinfo(){
    clearAll();
}

LoadLevelinfo *LoadLevelinfo::createLoadLevelinfo(const std::string& plistpath){
    LoadLevelinfo *pRet = new LoadLevelinfo();
    if (pRet && pRet->initPlist(plistpath)){
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool LoadLevelinfo::initPlist(const std::string& plistpath){
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plistpath);
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
        
    resources = dict["resources"].asValueMap();
    levelInfo = dict["levelInfo"].asValueMap();

    return true;
}

void LoadLevelinfo::clearAll(){
    resources.clear();
    levelInfo.clear();
}

void LoadLevelinfo::readLevelInfo(){
    GameManager* instance = GameManager::getInstance();
    
    auto money = levelInfo["money"].asInt();
    instance->setMoney(money);
    auto currLevel = levelInfo["currLevel"].asString();
    instance->setCurrLevelFile(currLevel);
    auto nextLevel = levelInfo["nextLevel"].asString();
    instance->setNextLevelFile(nextLevel);
    
    auto groupDict = levelInfo["group"].asValueMap();
    auto groupTotal = groupDict.size();
    instance->setGroupNum(groupTotal);
    
    for (auto i = groupDict.begin(); i != groupDict.end(); ++i) {
        auto group = i->second.asValueMap();
        
        auto type1Num = group["type1Num"].asInt();
        auto type2Num = group["type2Num"].asInt();
        auto type3Num = group["type3Num"].asInt();
        auto type1Hp = group["type1Hp"].asInt();
        auto type2Hp = group["type2Hp"].asInt();
        auto type3Hp = group["type3Hp"].asInt();
        
        GroupEnemy* groupEnemy = GroupEnemy::create();
        groupEnemy->initGroupEnemy(type1Num, type1Hp, type2Num, type2Hp, type3Num, type3Hp);
        instance->groupEnemyVector.pushBack(groupEnemy);
    }
    
    auto currMapName = resources["map"].asString();
    instance->setCurrMapName(currMapName);
    auto currBackgroundName = resources["background"].asString();
    instance->setCurrBackgroundName(currBackgroundName);
    
}

