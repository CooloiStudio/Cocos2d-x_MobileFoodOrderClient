//
//  mod_custom_info.h
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/15/15.
//
//

#ifndef __MobileFoodOrderClient__mod_custom_info__
#define __MobileFoodOrderClient__mod_custom_info__

#include "iostream"
#include "cocos2d.h"

USING_NS_CC;

class ModCustomInfo : public Layer
{
#pragma mark - Initialization
public:
    ModCustomInfo(){}
    ~ModCustomInfo(){}
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(ModCustomInfo);
};

#endif /* defined(__MobileFoodOrderClient__mod_custom_info__) */
