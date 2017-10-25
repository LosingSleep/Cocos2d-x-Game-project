//
//  Bullet.hpp
//  MyGame
//
//  Created by 陈晖 on 16/6/1.
//
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include "cocos2d.h"

//Set the enum value to judge what kind tower;
using Type = enum {ATTACK = 0, COLD, MULTIDIR, ATTACKUP, COLDUP, MULTIDIRUP};

//the speed means the moving time so the value smaller,the real speed faster;
const float SPEED[] = {0.5f, 4, 3, 1, 3, 2};

//Set the tower lethality;
const int LETHALITY[] = {10, 30, 15, 20, 40, 20};
const std::string PICTURE[] = {"bullet.png", "snowbullet.png", "multiDirTowerBullet.png",
                               "superBullet1.png", "superBullet3.png", "superBullet2.png"};

class Bullet: public cocos2d::Sprite {
public:
    Bullet();
    ~Bullet();

	//Initialize all kinds of date;
    virtual bool init(Type t);

	//calling the init fountion and automaticaly deal with the pointer;
    static Bullet* create(Type t);

    void removeBullet(cocos2d::Node* pSender);

	//run the bullet's action;
    void shoot();
    
    cocos2d::Vec2 towerPos;
protected:
	//Set the lethality;
    CC_SYNTHESIZE(int, lethality, Lethality);

	//Set the running speed;
    CC_SYNTHESIZE(float, speed, Speed);
    
	//the pointer is passed to shoot fountion;
    cocos2d::MoveTo* bulletAction;

	//To initialize the bullet picture;
    cocos2d::Sprite* sprite;

	//As a tag to judge what kind bullet;
    Type type;
};


#endif /* Bullet_hpp */