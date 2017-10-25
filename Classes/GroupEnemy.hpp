//
//  GroupEnemy.hpp
//  MyGame
//
//  Created by 陈晖 on 16/6/5.
//
//

#ifndef GroupEnemy_hpp
#define GroupEnemy_hpp

#include "cocos2d.h"

/*A class to store all the information of a group of enemy.*/

class GroupEnemy: public cocos2d::Node{
public:
    virtual bool init();
    CREATE_FUNC(GroupEnemy);
    
    GroupEnemy* initGroupEnemy(int type1Total, int type1Hp, int type2Total, int type2Hp, int type3Total, int type3Hp);
    
    CC_SYNTHESIZE(int, type1Total, Type1Total);
    CC_SYNTHESIZE(int, type2Total, Type2Total);
    CC_SYNTHESIZE(int, type3Total, Type3Total);
    CC_SYNTHESIZE(int, type1Hp, Type1Hp);
    CC_SYNTHESIZE(int, type2Hp, Type2Hp);
    CC_SYNTHESIZE(int, type3Hp, Type3Hp);
    CC_SYNTHESIZE(int, enemyTotal, EnemyTotal);
    CC_SYNTHESIZE(bool, isGroupAddFinished, IsGroupAddFinished);
};

#endif /* GroupEnemy_hpp */
