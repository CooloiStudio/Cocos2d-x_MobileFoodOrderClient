//
//  mod_food_order.h
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 4/27/15.
//
//

#ifndef __MobileFoodOrderClient__mod_food_order__
#define __MobileFoodOrderClient__mod_food_order__

#include "cocos2d.h"
#include "iostream"

#include "json/document.h"
#include "json/rapidjson.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "network/HttpClient.h"

USING_NS_CC;

class FoodOrder : public Layer
{
private:
    
    
    
public:
    
    FoodOrder();
    ~FoodOrder();
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(FoodOrder);
    
};
#endif /* defined(__MobileFoodOrderClient__mod_food_order__) */
