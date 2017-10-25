//
//  GameManager.hpp
//  MyGame
//
//  Created by 陈晖 on 16/6/1.
//
//

#ifndef GameManager_hpp
#define GameManager_hpp

#include <iostream>
#include "cocos2d.h"
#include "Tower.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "GroupEnemy.hpp"

/*A singleton pattern to store all information of the game.
 *The whole game only has one instance, it could be referenced at all scene
 */
class GameManager {
public:
    cocos2d::Vector<Enemy*> enemyVector;
    cocos2d::Vector<Tower*> towerVector;
    cocos2d::Vector<Bullet*> bulletVector;
    cocos2d::Vector<GroupEnemy*> groupEnemyVector;
    
    CC_SYNTHESIZE(int, money, Money);
    CC_SYNTHESIZE(int, groupNum, GroupNum);
    CC_SYNTHESIZE(std::string, currMapName, CurrMapName);
    CC_SYNTHESIZE(std::string, currLevelFile, CurrLevelFile);
    CC_SYNTHESIZE(std::string, nextLevelFile, NextLevelFile);
    CC_SYNTHESIZE(bool, isAddGroupFinished, IsAddGroupFinished);
    CC_SYNTHESIZE(std::string, currBackgroundName, CurrBackgroundName);
    CC_SYNTHESIZE(bool, isBackgroundMusicPlay, IsBackgroundMusicPlay);
    CC_SYNTHESIZE(bool, isFirstTimeInit, IsFirstTimeInit);
    
    
    static GameManager* getInstance();

    void clearGameManager();
private:
    GameManager(){};
    static GameManager* instance;
    
    //using a private menber class to delete instance when the program stop.
    class Deleter {
    public:
        ~Deleter(){
            if (GameManager::instance) {
                delete instance;
            }
        }
    };
    //when the program exit, its destructor will be called, then delete the instance.
    static Deleter deleter;
};
#endif /* GameManager_hpp */
