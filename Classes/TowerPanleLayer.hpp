//
//  TowerPanleLayer.hpp
//  MyGame
//
//  Created by 陈晖 on 16/5/31.
//
//

#ifndef TowerPanleLayer_hpp
#define TowerPanleLayer_hpp

#include <stdio.h>
#include "cocos2d.h"

typedef enum{
    ARROW_TOWER = 0,
    ATTACK_TOWER,
    MULTIDIR_TOWER,
    ANOTHER
} TowerType;

class TowerPanleLayer: public cocos2d::Layer {
public:
    
    TowerPanleLayer();
    ~TowerPanleLayer();
    virtual bool init() override;
    CREATE_FUNC(TowerPanleLayer);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) override;
    
    CC_SYNTHESIZE(TowerType, choseTowerType, ChoseTowerType);
    
private:
    cocos2d::Sprite* sprite1;
    cocos2d::Sprite* sprite2;
    cocos2d::Sprite* sprite3;
};

#endif /* TowerPanleLayer_hpp */
