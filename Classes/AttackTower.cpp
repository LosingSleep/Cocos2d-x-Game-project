//
//  AttackTower.cpp
//  NoOneSurvival
//
//  Created by 陈晖 on 16/6/11.
//
//

#include "AttackTower.hpp"
#include "GameManager.hpp"


bool AttackTower::init() {
	if (!Tower::init()) {
		return false;
	}

	setScope(220);
	setTowerValue(300);
	setRate(0.3f);

	//the AttackTower is formed by a baseplate ,a berrel ,and shooting bullets;
	baseplate = Sprite::createWithSpriteFrameName("attackTowerBase.png");
	addChild(baseplate);

	rotateArrow = Sprite::createWithSpriteFrameName("arrow.png");
	rotateArrow->setPosition(0, 0);
	addChild(rotateArrow);

	//using the schedule to realize shooting frequency;
	schedule(schedule_selector(AttackTower::rotateAndShoot), getRate());

	return true;

}

void AttackTower::rotateAndShoot(float dt) {

	checkNearestEnemy();
	if (nearestEnemy != NULL) {
		//get the rotational vector from the tower to the enemy;
		cocos2d::Vec2 rotateVector = nearestEnemy->getPosition() - this->getPosition();

		//get the angle form the vector;
		float rotateRadians = rotateVector.getAngle();

		//make the angle to degrees;
		float rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateRadians);

		//the speed is the berrel rotate speed;
		float speed = 0.3 / M_PI;

		//the time is cost in the rotation;
		float rotateDuration = fabs(rotateRadians * speed);

		//run the rotational action;
		rotateArrow->runAction(cocos2d::Sequence::create(cocos2d::RotateTo::create(rotateDuration, rotateDegrees),
			cocos2d::CallFunc::create(CC_CALLBACK_0(AttackTower::shoot, this)),
			NULL));
	}
}

Bullet* AttackTower::addAttackTowerBullet(){
    
    Type t = ATTACK;
    if (getIsUpgrade() == true) {
        t = Type::ATTACKUP;
    }
    
	//create a bullet by Type t;
    auto bullet = Bullet::create(t);

	//Record the parent node,the tower position;
    cocos2d::Vec2 towerPos = this->getPosition();

    bullet->towerPos = towerPos;
    this->addChild(bullet);
    return bullet;
}

void AttackTower::shoot(){
    GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;
    
    if (nearestEnemy != NULL && nearestEnemy->getCurrentHp() > 0){
        auto currBullet = addAttackTowerBullet();
        instance->bulletVector.pushBack(currBullet);
        
        auto moveDuration = currBullet->getSpeed();
		//calculate the direction between tower and nearest enemy;
        cocos2d::Vec2 shootVector = nearestEnemy->getPosition() - this->getPosition();
        cocos2d::Vec2 normalizedShootVector;

		//Make the vector to be normalized;
        normalizedShootVector.subtract(shootVector.getNormalized());

		//Get the farthest attack scope;
        auto farthestDistance = cocos2d::Director::getInstance()->getWinSize().width;

		//Get the attack scope of each bullet;
        cocos2d::Vec2 overshotVector = normalizedShootVector * farthestDistance;

		//Calculate the farthest node from the parent node by each bullet;
        cocos2d::Vec2 offscreenPoint = (rotateArrow->getPosition() - overshotVector);
        
        currBullet->bulletAction = cocos2d::MoveTo::create(moveDuration, offscreenPoint);
        currBullet->shoot();
        currBullet = NULL;
    }
}

//Upgrade the tower;
void AttackTower::upgrade(){
    towerValue += 500;
    scope += 20;
    rate -= 0.1f;
    
    rotateArrow->removeFromParent();
    rotateArrow = Sprite::createWithSpriteFrameName("arrowUp.png");
    this->addChild(rotateArrow);
    baseplate->removeFromParent();
    baseplate = Sprite::createWithSpriteFrameName("attackTowerBaseUp.png");
    this->addChild(baseplate, -10);
    
    setIsUpgrade(true);
}

