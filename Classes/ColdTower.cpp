//
//  ColdTower.cpp
//  NoOneSurvival
//
//  Created by 陈晖 on 16/6/11.
//
//

#include "ColdTower.hpp"
#include "GameManager.hpp"



bool ColdTower::init(){
    if (!Tower::init()) {
        return false;
    }
    
    setScope(330);
    setTowerValue(400);
    setRate(1.0f);
    
    
    baseplate = Sprite::createWithSpriteFrameName("coldTower.jpg");
    this->addChild(baseplate);
    
    schedule(schedule_selector(ColdTower::shoot), getRate());
    return true;
}


Bullet* ColdTower::addColdTowerBullet(){
    Type t = COLD;
    if (getIsUpgrade() == true) {
        t = Type::COLDUP;
    }
    
    auto bullet = Bullet::create(t);
    cocos2d::Vec2 towerPos = this->getPosition();
    bullet->towerPos = towerPos;
    this->addChild(bullet);
    return bullet;
}

void ColdTower::shoot(float dt){
    GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;
    
    checkNearestEnemy();
    
    if (nearestEnemy != NULL && nearestEnemy->getCurrentHp() > 0){
        auto currBullet = addColdTowerBullet();
        instance->bulletVector.pushBack(currBullet);
        
        auto moveDuration = currBullet->getSpeed();

		//Record the vector between tower and enemy;
        cocos2d::Point shootVector(nearestEnemy->getPosition() - this->getPosition());
        cocos2d::Point normalizedShootVector;

		//Get the subtraactive value of the normalized vector;
        normalizedShootVector.subtract(shootVector.getNormalized());
        
        auto farthestDistance = cocos2d::Director::getInstance()->getWinSize().width;

		//Get the farthest attack scope;
        cocos2d::Point overshotVector = normalizedShootVector * farthestDistance;

		//Get the farthest arrival node from the parent node(tower position);
        cocos2d::Point offscreenPoint = (baseplate->getPosition() - overshotVector);
        
        currBullet->bulletAction = cocos2d::MoveTo::create(moveDuration, offscreenPoint);
        currBullet->shoot();
        currBullet = NULL;
    }
}


//Upgrade the tower;
void ColdTower::upgrade(){
    towerValue += 500;
    scope += 20;
    
    baseplate->removeFromParent();
    baseplate = Sprite::createWithSpriteFrameName("coldTowerUp.png");
    this->addChild(baseplate);
    
    setIsUpgrade(true);
}