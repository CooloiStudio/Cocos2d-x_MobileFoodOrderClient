//
//  mod_food_show.h
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/28/15.
//
//

#ifndef __MobileFoodOrderClient__mod_food_show__
#define __MobileFoodOrderClient__mod_food_show__

#include "iostream"
#include "cocos2d.h"
#include "mod_http.h"
#include "mod_check.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace extension;
using namespace ui;

class ModFoodShow : public Node
{
private:
    
    int food_id_;
    Sprite* img_;
    ModHttp* mod_http_;
    EventListener* listener_;
    
public:
    ModFoodShow();
    ~ModFoodShow();
    bool init();
    static ModFoodShow* Create(int id);
    
public:
    
#pragma mark - Interface
    
    void SetFoodId(int food_id){food_id_ = food_id;}
    int GetFoodId() {return food_id_;}
    
#pragma mark - Function
    
    int InitFoodShow();
    

};

#endif /* defined(__MobileFoodOrderClient__mod_food_show__) */
