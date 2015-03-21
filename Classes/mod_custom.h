//
//  mod_custom.h
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/15/15.
//
//

#ifndef __MobileFoodOrderClient__mod_custom__
#define __MobileFoodOrderClient__mod_custom__

#include "iostream"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "mod_custom_info.h"
#include "mod_main_menu.h"
#include "info.h"

USING_NS_CC;
using namespace ui;

class ModCustom : public Layer
{
private:
    Layer* layer_top_;
    Layer* layer_food_;
    
    
#pragma mark - Initialization
public:
    ModCustom();
    ~ModCustom(){}
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(ModCustom);
    
public:
    
    
    
    void InitTop();
    
    
    void ButtonBackCallback(Ref* pSender, Widget::TouchEventType type);
    void ButtonInfoCallback(Ref* pSender, Widget::TouchEventType type);
};

#endif /* defined(__MobileFoodOrderClient__mod_custom__) */
