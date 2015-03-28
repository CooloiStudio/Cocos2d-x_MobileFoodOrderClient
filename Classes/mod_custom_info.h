//
//  mod_custom_info.h
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/15/15.
//
//

#ifndef __MobileFoodOrderClient__mod_custom_info__
#define __MobileFoodOrderClient__mod_custom_info__

#include "iostream"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "mod_shopping.h"

USING_NS_CC;
using namespace ui;

class ModCustomInfo : public Layer
{
private:
    LayerColor* layer_top_;
    
#pragma mark - Initialization
public:
    ModCustomInfo(){}
    ~ModCustomInfo(){}
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(ModCustomInfo);
    
public:
    
    void InitTop();
    void ButtonBackCallback(Ref* pSender, Widget::TouchEventType type);
    void ButtonShopCallback(Ref* pSender, Widget::TouchEventType type);
};

#endif /* defined(__MobileFoodOrderClient__mod_custom_info__) */
