//
//  mod_custom_info.cpp
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/15/15.
//
//

#include "mod_custom_info.h"

bool ModCustomInfo::init()
{
    return true;
}

Scene* ModCustomInfo::createScene()
{
    auto scene = Scene::create();
    auto layer = Layer::create();
    scene->addChild(layer);
    return scene;
}

