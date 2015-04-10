//
//  mod_food_info.cpp
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/29/15.
//
//

#include "mod_food_info.h"


ModFoodInfo::ModFoodInfo(int food_id):
food_id_(food_id)
{
    
}

ModFoodInfo::~ModFoodInfo()
{
    
}

ModFoodInfo* ModFoodInfo::CreateScene(int food_id)
{
    auto* ret = new ModFoodInfo(food_id);
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool ModFoodInfo::init()
{
    return true;
}