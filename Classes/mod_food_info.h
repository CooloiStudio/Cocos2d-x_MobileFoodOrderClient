//
//  mod_food_info.h
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/29/15.
//
//

#ifndef __MobileFoodOrderClient__mod_food_info__
#define __MobileFoodOrderClient__mod_food_info__

#include "iostream"
#include "cocos2d.h"

USING_NS_CC;

class ModFoodInfo : public Scene
{
private:
    
    int food_id_;
    
    
public:
    ModFoodInfo(int food_id);
    ~ModFoodInfo();
    bool init();
    static ModFoodInfo* CreateScene(int food_id);

};


#endif /* defined(__MobileFoodOrderClient__mod_food_info__) */
