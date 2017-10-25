//
//  Tower.hpp
//  MyGame
//
//  Created by 陈晖 on 16/6/1.
//
//

#ifndef Tower_hpp
#define Tower_hpp

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "Enemy.hpp"
#include "Bullet.hpp"

class Tower: public cocos2d::Sprite {
public:
	Tower();

	~Tower();

	virtual bool init();

	CREATE_FUNC(Tower);


	void checkNearestEnemy();

	//the base class's virtual fountion;
    virtual void upgrade(){};

	//Set the shooting scope;
	CC_SYNTHESIZE(int, scope, Scope);

	//Set the shooting frequency;
	CC_SYNTHESIZE(float, rate, Rate);

	//Set the money of the tower;
	CC_SYNTHESIZE(int, towerValue, TowerValue);

	//Set a tag to judge whether the tower can be upgraded;
    CC_SYNTHESIZE(bool, isUpgrade, IsUpgrade);
    
protected:
	//Record the enemy by fountion 'checkNearestEnemy()';
    Enemy* nearestEnemy;

};

#endif /* Tower_hpp */
