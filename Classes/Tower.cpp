//
//  Tower.cpp
//  MyGame
//
//  Created by 陈晖 on 16/6/1.
//
//

#include "Tower.hpp"
#include "GameManager.hpp"

USING_NS_CC;

Tower::Tower():
nearestEnemy(NULL)
,scope(0)
,rate(0)
,towerValue(0)
,isUpgrade(false)
{};

Tower::~Tower(){};

bool Tower::init(){
    if (!Sprite::init()) {
        return false;
    }
    
    return true;
}

void Tower::checkNearestEnemy() {
    GameManager* instance = GameManager::getInstance();
    auto enemyVector = instance->enemyVector;
    
    auto currMinDistant = this->scope;

    Enemy *enemyTemp = NULL;
    
    for (int i = 0; i < enemyVector.size(); i++) {
        auto enemy = enemyVector.at(i);
        double distance = this->getPosition().getDistance(enemy->getPosition());
        if (distance < currMinDistant) {
            currMinDistant = distance;
            enemyTemp = enemy;
        }
    }

    nearestEnemy = enemyTemp;
}