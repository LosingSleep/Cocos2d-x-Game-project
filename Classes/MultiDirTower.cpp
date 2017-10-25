//
//  MultiDirTower.cpp
//  NoOneSurvival
//
//  Created by 陈晖 on 16/6/11.
//
//

#include "MultiDirTower.hpp"
#include "GameManager.hpp"

bool MultiDirTower::init(){
    if (!Tower::init()) {
        return false;
    }
    
    setScope(255);
    setTowerValue(500);
    setRate(0.7f);
    setDirTotal(6);
    
    multiDirTower = Sprite::createWithSpriteFrameName("multiDirTower.png");
    this->addChild(multiDirTower);
    
	//Realize the shooting frequency by using the schedule;
    this->schedule(schedule_selector(MultiDirTower::shoot), getRate());
    
    return true;
}


Bullet* MultiDirTower::addMultiDirTowerBullet(){
    Type t = MULTIDIR;
    if (getIsUpgrade() == true) {
        t = Type::MULTIDIRUP;
    }
    
    auto bullet = Bullet::create(t);

	//Set the original position of the bullet;
    cocos2d::Vec2 towerPos = this->getPosition();
    cocos2d::Vec2 bulletPos =cocos2d::Vec2(0, multiDirTower->getContentSize().height / 4);

	//Record the tower position;
    bullet->towerPos = towerPos;
    bullet->setPosition(bulletPos);
    this->addChild(bullet);
    return bullet;
}

void MultiDirTower::shoot(float dt){
    GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;
    
    int dirTotal = getDirTotal();
    this->checkNearestEnemy();
    
    if (nearestEnemy != NULL && nearestEnemy->getCurrentHp() > 0){
        for (int i = 0; i < dirTotal; i++){
            auto currBullet = addMultiDirTowerBullet();
            instance->bulletVector.pushBack(currBullet);

			//Get the time in the moving process; 
            auto moveDuration = currBullet->getSpeed();
            cocos2d::Vec2 shootVector;
            shootVector.x = 1;
            shootVector.y = tan(i * 2 * M_PI / dirTotal);

			//Set every bullet's shooting direction;
            cocos2d::Vec2 normalizedShootVector;
            if (i >= dirTotal / 2) {
                normalizedShootVector += shootVector.getNormalized();
            }
            else {
                normalizedShootVector -= shootVector.getNormalized();
            }
            auto farthestDistance = cocos2d::Director::getInstance()->getWinSize().width;

			//Get the farthest distacne on the exact direction;
            cocos2d::Vec2 overshotVector = normalizedShootVector * farthestDistance;

			//Get the farthest node from the parent node;
            cocos2d::Vec2 offscreenPoint = (currBullet->getPosition() - overshotVector);

			//run the moving action;
            currBullet->bulletAction = cocos2d::MoveTo::create(moveDuration, offscreenPoint);
            currBullet->shoot();
            currBullet = NULL;
        }
    }
}


//Upgrade the tower,adding the shooting direction,value,scope;
void MultiDirTower::upgrade(){
    dirTotal += 4;
    towerValue += 500;
    scope += 20;
    
	//Replace the original sprite by a new picture;
    multiDirTower->removeFromParent();
    multiDirTower = Sprite::createWithSpriteFrameName("multiDirTowerUp.png");
    this->addChild(multiDirTower);
    
	//Set the tag to be true, which will be used to judge whether the tower can be upgrade;
    setIsUpgrade(true);
}
