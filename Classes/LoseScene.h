#include"cocos2d.h"

class LoseScene : public cocos2d::Scene{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(LoseScene);
	
	//button to change scene to levelSelectedScene
	void menuBackCallback(Ref* psender);

	//button to change scene to levelInfoScene
	void menuTryAgainCallback(Ref* psender);

	//buttons to pause and resume music
	void menuMusicStop(Ref* psender);
	void menuMusicStart(Ref* psender);
}; 
