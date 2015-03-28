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
    auto layer_background = LayerColor::create(Color4B(240,240,255,255));
    addChild(layer_background);
    InitTop();
    return true;
}

Scene* ModCustomInfo::createScene()
{
    auto scene = Scene::create();
    auto layer = ModCustomInfo::create();
    scene->addChild(layer);
    return scene;
}

void ModCustomInfo::InitTop()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto size = Director::getInstance()->getVisibleSize();
    layer_top_ = LayerColor::create(Color4B(244, 245, 255, 255));
    layer_top_->setContentSize(Size(size.width,size.height / 15));
    layer_top_->setPosition(Vec2(origin.x + 0,origin.y + size.height / 15 * 14));
    layer_top_->setCascadeColorEnabled(true);
    //    layer_top_->setColor(Color3B(128,128,128));
    
    auto label_title = Label::createWithSystemFont("我的信息", "Arial", 24);
    label_title->setDimensions(layer_top_->getContentSize().width / 4, layer_top_->getContentSize().height);
    label_title->setPosition(Vec2(layer_top_->getPositionX() + size.width / 2,layer_top_->getPositionY() + label_title->getContentSize().height / 2));
    label_title->setTextColor(Color4B(102,102,102,255));
    label_title->setAlignment(cocos2d::TextHAlignment::CENTER);
    label_title->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    
    
    auto button_back = Button::create("back.png");
    auto scale = layer_top_->getContentSize().height/ button_back->getContentSize().height * 0.8;
    button_back->setScale(scale);
    log("size %f",button_back->getContentSize().width );
    button_back->setPosition(Vec2(layer_top_->getPositionX() + button_back->getContentSize().width / 2 * scale,layer_top_->getPositionY() + layer_top_->getContentSize().height / 2));
    button_back->addTouchEventListener(CC_CALLBACK_2(ModCustomInfo::ButtonBackCallback, this));
    
    auto button_info = Button::create("shop.png");
    button_info->setScale(scale);
    button_info->setPosition(Vec2(layer_top_->getPositionX() + size.width - button_back->getContentSize().width / 2 * scale,layer_top_->getPositionY() + layer_top_->getContentSize().height / 2));
//    button_info->addTouchEventListener(CC_CALLBACK_2(ModCustom::ButtonBackCallback, this));
    
    
    addChild(button_back,2);
    addChild(button_info,2);
    addChild(label_title,2);
    addChild(layer_top_,1);
}

void ModCustomInfo::ButtonBackCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
    Director::getInstance()->popScene();
}