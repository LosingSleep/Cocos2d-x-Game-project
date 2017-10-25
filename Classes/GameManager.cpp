//
//  GameManager.cpp
//  MyGame
//
//  Created by 陈晖 on 16/6/1.
//
//

#include "GameManager.hpp"

USING_NS_CC;

GameManager* GameManager::instance = NULL;

GameManager* GameManager::getInstance(){
    if (instance == NULL) {
        instance = new GameManager();
    }
    
    return instance;
}

void GameManager::clearGameManager(){
    enemyVector.clear();
    bulletVector.clear();
    towerVector.clear();
    groupEnemyVector.clear();
    
    return ;
}