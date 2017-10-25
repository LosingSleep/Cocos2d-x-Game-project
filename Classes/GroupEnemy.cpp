//
//  GroupEnemy.cpp
//  MyGame
//
//  Created by 陈晖 on 16/6/5.
//
//

#include "GroupEnemy.hpp"

USING_NS_CC;

bool GroupEnemy::init(){
    if (!Node::init()) {
        return  false;
    }
    return true;
}

GroupEnemy* GroupEnemy::initGroupEnemy(int type1Total, int type1Hp, int type2Total, int type2Hp, int type3Total, int type3Hp){
    this->setType1Total(type1Total);
    this->setType1Hp(type1Hp);
    this->setType2Total(type2Total);
    this->setType2Hp(type2Hp);
    this->setType3Total(type3Total);
    this->setType3Hp(type3Hp);
    this->enemyTotal = type1Total + type2Total + type3Total;
    this->setIsGroupAddFinished(false);
    return this;
}

