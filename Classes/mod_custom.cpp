//
//  mod_custom.cpp
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/15/15.
//
//

#include "mod_custom.h"

ModCustom::ModCustom()
{
    
}

Scene* ModCustom::createScene()
{
    auto scene = Scene::create();
    auto layer = ModCustom::create();
    scene->addChild(layer,0);
    return scene;
}

bool ModCustom::init()
{
    auto layer_background = LayerColor::create(Color4B(221,221,221,255));
    InitTop();
    InitFood();
    addChild(layer_background, 0);
    return true;
}

void ModCustom::InitFood()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
//    layer_ = Layer::create();
    layer_list_ = ScrollView::create();
    layer_list_->setViewSize(Size(Director::getInstance()->getVisibleSize().width,Director::getInstance()->getVisibleSize().height - layer_top_->getContentSize().height));
    layer_list_->setBounceable(true);
    layer_list_->setDirection(ScrollView::Direction::VERTICAL);
    addChild(layer_list_,2);
    layer_list_->setPosition(Vec2(origin.x,
                                  layer_list_->getPositionY()));
    auto* food = ModFoodShow::Create(0);
//    food->setPosition(origin.x,layer_list_->getPositionY() + Director::getInstance()->getVisibleSize().height * 4 / 5 - layer_top_->getContentSize().height);
    log("add first food");
    food->setPosition(-origin.x,origin.y);
    layer_list_->addChild(food);
    layer_food_.push_back(food);
    
    for (int i = 0 ; i < 8 ; i++)
    {
        auto* food1 = ModFoodShow::Create(0);
        food1->setPosition(-origin.x,
                           layer_food_[layer_food_.size() - 1]->getPositionY() + food1->getContentSize().height + 5);
        layer_list_->addChild(food1);
        layer_food_.push_back(food1);
        log("add food%d",i);
    }
//    layer_list_->addChild(layer_);
//    layer_->setContentSize(Size(Director::getInstance()->getVisibleSize().width,
//                                     layer_food_.size() * 300));
    layer_list_->setContentSize(Size(Director::getInstance()->getVisibleSize().width,
                                     layer_food_.size() * (food->getContentSize().height + 5)));
    layer_list_->setContentOffset(Vec2(layer_list_->getPositionX(),
                                  0 -layer_list_->getContentSize().height + Director::getInstance()->getVisibleSize().height - layer_top_->getContentSize().height));
    
//    auto layer = LayerColor::create(Color4B(0,0,0,255));
////    layer->setContentSize(Size(2048,200));
//    layer_list_->addChild(layer,60);
    log("add layer list");
    AddListener();
    
    layer_list_->setDelegate(this);
}







void ModCustom::InitTop()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    auto size = Director::getInstance()->getVisibleSize();
    layer_top_ = LayerColor::create(Color4B(249, 249, 249, 255));
    layer_top_->setContentSize(Size(size.width,size.height / 15));
    layer_top_->setPosition(Vec2(origin.x + 0,origin.y + size.height / 15 * 14));
    layer_top_->setCascadeColorEnabled(true);
//    layer_top_->setColor(Color3B(128,128,128));
    
    auto label_title = Label::createWithSystemFont("美食列表", "Arial", 24);
    label_title->setDimensions(layer_top_->getContentSize().width / 4, layer_top_->getContentSize().height);
    label_title->setPosition(Vec2(layer_top_->getPositionX() + size.width / 2, layer_top_->getPositionY() + label_title->getContentSize().height / 2));
    label_title->setTextColor(Color4B(102,102,102,255));
    label_title->setAlignment(cocos2d::TextHAlignment::CENTER);
    label_title->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    
    
    auto button_back = Button::create("back.png");
    auto scale = layer_top_->getContentSize().height/ button_back->getContentSize().height * 0.8;
    button_back->setScale(scale);
    log("size %f",button_back->getContentSize().width );
    button_back->setPosition(Vec2(layer_top_->getPositionX() + button_back->getContentSize().width / 2 * scale, layer_top_->getPositionY() + layer_top_->getContentSize().height / 2));
    button_back->addTouchEventListener(CC_CALLBACK_2(ModCustom::ButtonBackCallback, this));
    
    auto button_info = Button::create("info.png");
    button_info->setScale(scale);
    button_info->setPosition(Vec2(layer_top_->getPositionX() + size.width - button_back->getContentSize().width / 2 * scale, layer_top_->getPositionY() + layer_top_->getContentSize().height / 2));
    button_info->addTouchEventListener(CC_CALLBACK_2(ModCustom::ButtonInfoCallback, this));
    
    
    addChild(button_back,51);
    addChild(button_info,51);
    addChild(label_title,51);
    addChild(layer_top_,50);
}

void ModCustom::ButtonBackCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void ModCustom::ButtonInfoCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
    if (LogInfo::GetLogIn() == 0)
    {
        Director::getInstance()->pushScene(ModCustomInfo::createScene());
    }
    else
    {
        Director::getInstance()->pushScene(ModMainMenu::createScene(0));
    }
    log("Touch Info");
}

bool ModCustom::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event* event)
{
    log("ModMsgBox::onTouchBegan");
    
    touch_began_ = touch->getLocation();
    
    return true;
} // ModMsgBox::onTouchBegan

void ModCustom::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (50 > abs(touch->getLocation().x - touch_began_.x) && 50 > abs(touch->getLocation().y - touch_began_.y))
    {
    
    auto location = this->convertToNodeSpace(touch->getLocation());
    if (0 == ModCheck::CheckContainsPoint(layer_food_[0], layer_list_,location))
    {
        log("touch in layer");
        return;
    }
    }
    
} //  ModMsgBox::onTouchEnded

void ModCustom::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
//    layer_list_->setPosition(Vec2(layer_list_->getPosition().x,
//                                  layer_list_->getPosition().y + touch->getDelta().y));
//    layer_list_->setPosition(Vec2(layer_list_->getPosition().x + touch->getDelta().x,
//                                  layer_list_->getPosition().y + touch->getDelta().y));
    
    log("ModMsgBox::onTouchMoved");
} // ModMsgBox::onTouchMoved

void ModCustom::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return;
}

int ModCustom::AddListener()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(ModCustom::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(ModCustom::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(ModCustom::onTouchMoved, this);
    listener->onTouchCancelled = CC_CALLBACK_2(ModCustom::onTouchCancelled, this);
    
    listener_ = listener;
    return 0;
} // ModMsgBox::AddListener
