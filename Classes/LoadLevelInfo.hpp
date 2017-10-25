//
//  LoadLevelInfo.hpp
//  NoOneSurvival
//
//  Created by 陈晖 on 16/6/9.
//
//

#ifndef LoadLevelInfo_hpp
#define LoadLevelInfo_hpp

#include <stdio.h>
#include "cocos2d.h"

class LoadLevelinfo: public cocos2d::Ref{
public:
    
    ~LoadLevelinfo();
    static LoadLevelinfo * createLoadLevelinfo(const std::string& plistpath);
    
	//to get information of current level from the plist
    bool initPlist(const std::string& plistpath);
    
	//to read the file of the level and to load the enemy and other resource 
	void readLevelInfo();
    
	void clearAll();
    
private:
	
	//the resource used in the level
    cocos2d::ValueMap resources;

	//player's history record of the level
    cocos2d::ValueMap levelInfo;
};
#endif /* LoadLevelInfo_hpp */
