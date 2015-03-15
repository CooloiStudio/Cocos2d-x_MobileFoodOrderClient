//
//  mod_shopping.cpp
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/15/15.
//
//

#include "mod_shopping.h"

Scene* ModShopping::createScene()
{
    auto scene = Scene::create();
    auto layer = ModShopping::create();
    scene->addChild(layer);
    return scene;
}

bool ModShopping::init()
{
    return true;
}