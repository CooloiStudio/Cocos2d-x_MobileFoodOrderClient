//
//  mod_check.h
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/28/15.
//
//

#ifndef __MobileFoodOrderClient__mod_check__
#define __MobileFoodOrderClient__mod_check__

#include "cocos2d.h"

USING_NS_CC;

class ModCheck
{
public:
    static int CheckContainsPoint(Node* object, Vec2 location);
    static int CheckContainsPoint(Node* object, Node* bg, Vec2 location);
};

#endif /* defined(__MobileFoodOrderClient__mod_check__) */
