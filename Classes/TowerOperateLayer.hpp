//
//  TowerOperateLayer.hpp
//  NoOneSurvival
//
//  Created by 陈晖 on 16/6/16.
//
//

#ifndef TowerOperateLayer_hpp
#define TowerOperateLayer_hpp

#include "cocos2d.h"

typedef enum{
    DELETE = 0,
    UPGRADE,
    CANCEL
} OperateType;

class TowerOperateLayer: public cocos2d::Layer {
public:
    
    TowerOperateLayer();
    ~TowerOperateLayer();
    virtual bool init() override;
    CREATE_FUNC(TowerOperateLayer);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) override;

    CC_SYNTHESIZE(OperateType, choseOperateType, ChoseOperateType);
    
private:
    cocos2d::Sprite* sprite1;
    cocos2d::Sprite* sprite2;
};
#endif /* TowerOperateLayer_hpp */
