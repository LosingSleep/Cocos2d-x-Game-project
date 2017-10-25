#include"cocos2d.h"

class WinScene : public cocos2d::Scene{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(WinScene);

    //button to change the scene to next level
	void menuContinueCallback(Ref* psender);
	
	//button to change the scene to levelselectedscene
	void menuBackCallback(Ref* psender);

	//buttons to pause and resume music
	void menuMusicStop(Ref* psender);
	void menuMusicStart(Ref* psender);
}; 
