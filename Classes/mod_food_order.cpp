//
//  mod_food_order.cpp
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 4/27/15.
//
//

#include "mod_food_order.h"

FoodOrder::FoodOrder()
{
    
}

FoodOrder::~FoodOrder()
{
    
}

bool FoodOrder::init()
{
    
}

Scene* FoodOrder::createScene()
{
    auto scene = Scene::create();
    auto layer = FoodOrder::create();
    scene->addChild(layer);
    return scene;
}

