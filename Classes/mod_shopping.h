//
//  mod_shopping.h
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/15/15.
//
//

#ifndef __MobileFoodOrderClient__mod_shopping__
#define __MobileFoodOrderClient__mod_shopping__

#include "iostream"
#include "cocos2d.h"

USING_NS_CC;

class ModShopping : public Layer
{
#pragma mark - Initialization 
public:
    ModShopping(){}
    ~ModShopping(){}
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(ModShopping);
    
};

#endif /* defined(__MobileFoodOrderClient__mod_shopping__) */
