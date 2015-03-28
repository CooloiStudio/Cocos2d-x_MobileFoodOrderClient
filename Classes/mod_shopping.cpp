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
    mod_http = ModHttp::Create();
    addChild(mod_http);
    mod_http->DownloadPicture(0);
    return true;
}