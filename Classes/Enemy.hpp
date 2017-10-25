//
//  Enemy.hpp
//  MyGame
//
//  Created by 陈晖 on 16/5/25.
//
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "cocos2d.h"

using enemyType = enum{WAKING = 0, RUNNING, SKATING};

/*some information about different enemy*/

const float RUNSPEED[] = {5.0f, 1.0f, 3.0f};
const int VALUE[] = {30, 15, 50};

/*the pre-picture-name of the enemy, it has left and right two directions*/
const std::string RIGHT_FRAME_NAME[] = {"EnemyRight_1", "EnemyRight_2", "EnemyRight_3"};
const std::string LEFT_FRAME_NAME[] = {"EnemyLeft_1", "EnemyLeft_2", "EnemyLeft_3"};

/*how many frame the different enemy's animation have*/
const int FRAME_NAM[] = {6, 4, 4};

const float ANIMATION_DELAY[] = {0.5f, 0.3f, 0.4f};

/*animation names of enemy*/
const std::string RIGHT_ANIMATION_NAME[] = {"runRight_1", "runRight_2", "runRight_3"};
const std::string LEFT_ANIMATION_NAME[] = {"runLeft_1", "runLeft_2", "runLeft_3"};

class Enemy: public cocos2d::Sprite{
public:
    
    Enemy();
    ~Enemy();
    
    virtual bool init(enemyType t);
    static Enemy* create(cocos2d::Vector<Node *> points, int hp, enemyType t);
    
    //create an animation with the filename, frames' number, and delay.
    cocos2d::Animation* createAnimation(std::string prefixName, int framesNum, float delay);
    
    void createAndSetHpBar();
    
    Node* getCurrentPoint();
    Node* getNextPoint();
    
    //init the pointVector
    void setPointsVector(cocos2d::Vector<Node*> points);
    void runFollowPoint();
    
    virtual void changeDirection(float dt);
    virtual void enemyDead();
    
private:
    //store all the point that enemy need to run
    cocos2d::Vector<cocos2d::Node*> pointsVector;
    
protected:
    //record the type of the enemy
    CC_SYNTHESIZE(enemyType, type, Type);
    
    int pointCounter;
    
    //the animation when enemy's direction is facing right side.
    cocos2d::Animation *animationRight;
    
    //the animation when enemy's direction is facing left side.
    cocos2d::Animation *animationLeft;
    
    CC_SYNTHESIZE(float, runSpeed, RunSpeed);
    CC_SYNTHESIZE(float, maxHp, MaxHp);
    CC_SYNTHESIZE(int, vaule, Vaule);
    CC_SYNTHESIZE(float, currentHp, CurrentHp);
    CC_SYNTHESIZE(float, hpPercentage, HpPercentage);
    CC_SYNTHESIZE_READONLY(cocos2d::ProgressTimer*, hpBar, HpBar);
    CC_SYNTHESIZE(bool, enemySuccessful, EnemySuccessful);
    
    Sprite* sprite;
    Sprite* hpBackgroundSprite;
};

#endif /* Enemy_hpp */
