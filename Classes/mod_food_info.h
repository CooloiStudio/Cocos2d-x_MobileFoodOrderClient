//
//  mod_food_info.h
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/29/15.
//
//

#ifndef __MobileFoodOrderClient__mod_food_info__
#define __MobileFoodOrderClient__mod_food_info__

#include "iostream"
#include "cocos2d.h"

#include "json/document.h"
#include "json/rapidjson.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

#include "mod_custom_info.h"
#include "info.h"

#include "cocos-ext.h"
#include "custom_string.h"

USING_NS_CC;
using namespace  ui;
using namespace extension;

class ModFoodInfo : public Scene
{
private:
    int food_id_;
    int reget_;
    std::string canteen_;
    std::string name_;
    std::string img_ad_;
    std::string description_;
    std::string price_;
    
    LayerColor* layer_top_;
    LayerColor* layer_bottom_;
    
    std::string num_;
    
public:
    ModFoodInfo(std::string food);
    ~ModFoodInfo();
    bool init();
    static ModFoodInfo* CreateScene(std::string food_str);

public:
    
    void InitTop();
    void InitBottom();
    void InitFood();

    
    void ButtonBackCallback(Ref *psender, Widget::TouchEventType type);
    void ButtonInfoCallback(Ref *psender, Widget::TouchEventType type);
    void ButtonShopCallback(Ref *psender, Widget::TouchEventType type);
    
    
    
    virtual void editBoxEditingDigBegin(EditBox* editbox);
    virtual void editBoxEditingDidEnd(EditBox* editbox);
    virtual void editBoxTextChanged (EditBox *editBox, const std::string &text);
    virtual void editBoxReturn (EditBox *editBox);
    
    void BuySomething();
    void BuyCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    
};


#endif /* defined(__MobileFoodOrderClient__mod_food_info__) */
