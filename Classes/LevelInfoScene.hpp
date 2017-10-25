//
//  LevelInfoScene.hpp
//  NoOneSurvival
//
//  Created by 陈晖 on 16/6/16.
//
//

#ifndef LevelInfoScene_hpp
#define LevelInfoScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "LoadLevelInfo.hpp"

class LevelInfoScene: public cocos2d::Layer {
public:
    LevelInfoScene();;
    ~LevelInfoScene();
    CREATE_FUNC(LevelInfoScene);
    static cocos2d::Scene * createScene();
    
	//to get the information of current level and display your star level
	bool init();

	//to initialize the UI of the layer
    void addBackGround();
    
	//to change the scene to LevelScene
    void menuBackCallback(Ref* pSender);

	//start to play the game
    void menuStartCallback(Ref* pSender);
    
private:
	
   LoadLevelinfo* info;
   std::string fileName;
};

#endif /* LevelInfoScene_hpp */
