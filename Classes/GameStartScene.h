#ifndef __GAMESTART_SCENE_H__
#define __GAMESTART_SCENE_H__

#include "cocos2d.h"

class GameStart : public cocos2d::Layer{
public:
    GameStart();
    ~GameStart();
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameStart);

	void menuCloseCallback(Ref* psender);

	void menuChangeCallback(Ref* psender);

	void menuGuideCallback(Ref* psender);

	void menuMusicStop(Ref* psender);

	void menuMusicStart(Ref* psender);

};

#endif // __GAMESTART_SCENE_H__
