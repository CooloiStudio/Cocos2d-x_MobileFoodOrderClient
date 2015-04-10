//
//  mod_check.cpp
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/28/15.
//
//

#include "mod_check.h"

int ModCheck::CheckContainsPoint(cocos2d::Node *object, cocos2d::Vec2 location)
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto object_rect = Rect
    (
     object->getPosition().x,
     object->getPosition().y,
     object->getContentSize().width,
     object->getContentSize().height
     );
    return object_rect.containsPoint(location) ? 0 : 1;
}

int ModCheck::CheckContainsPoint(cocos2d::Node *object, Node* bg, cocos2d::Vec2 location)
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto object_rect = Rect
    (
     bg->getPositionX() + object->getPosition().x,
     bg->getPositionY() + object->getPosition().y,
     object->getContentSize().width,
     object->getContentSize().height
     );
    return object_rect.containsPoint(location) ? 0 : 1;
}