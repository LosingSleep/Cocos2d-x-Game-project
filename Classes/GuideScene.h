#ifndef _GUIDESCENE_H_
#define _GUIDESCENE_H_
#include"cocos2d.h"

class GuideScene : public cocos2d::Layer{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GuideScene);

	//to pop the scene
	void popScene(Ref* psender);
};
#endif