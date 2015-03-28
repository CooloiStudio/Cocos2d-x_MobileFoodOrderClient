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
#include "mod_http.h"

USING_NS_CC;

class ModShopping : public Layer
{
private:
    ModHttp* mod_http;
    
#pragma mark - Initialization 
public:
    ModShopping(){}
    ~ModShopping(){}
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(ModShopping);
    
public:
    
    void testDownload();
    
};

#endif /* defined(__MobileFoodOrderClient__mod_shopping__) */
