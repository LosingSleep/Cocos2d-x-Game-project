#ifndef __LEVELSELECTED_SCENE_H__
#define __LEVELSELECTED_SCENE_H__

#include "cocos2d.h"  

USING_NS_CC;

// nodes added to ScrollView layer
class LevelSelectPage : public Node{
public:

	//create the background of levelSelectedPage according to the name of picture
	//initialize three buttons on one page ,each leading to a different level
	//mark the button respectively in order to distinguish the level player choose
	bool initLevelPage(const std::string& bgName, int level);

	//to create the LevelSelectedPage
	static LevelSelectPage* create(const std::string& bgName, int level);

	//get the marked value of the button player press 
	//read tha data of this level according to the marked value
	void menuStartCallback(Ref* pSender);
};
#endif // __LEVELSELECTEDSCENE_SCENE_H__