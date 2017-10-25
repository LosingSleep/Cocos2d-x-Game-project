#ifndef __LEVELSCENE_SCENE_H__
#define __LEVELSCENE_SCENE_H__

#include <iostream>
#include "cocos2d.h"

//background scene to hold the ScrollView layer
class LevelScene : public cocos2d::Scene{
public:

	virtual bool init();
	CREATE_FUNC(LevelScene);
	
	//button to change the scene to GameStartScene
	void menuCloseCallback(Ref* pSender);

	//to make sure levelScene has been initialized
	static LevelScene *getInstance();

private:

	static LevelScene *instance;
};

#endif // __GAMESTART_SCENE_H__