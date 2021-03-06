//
//  mod_custom.h
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/15/15.
//
//

#ifndef __MobileFoodOrderClient__mod_custom__
#define __MobileFoodOrderClient__mod_custom__

#include "iostream"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "mod_custom_info.h"
#include "mod_main_menu.h"
#include "mod_food_show.h"
#include "mod_check.h"
#include "info.h"
#include "mod_config_json.h"

#include "json/document.h"
#include "json/rapidjson.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "network/HttpClient.h"

USING_NS_CC;
using namespace ui;
using namespace extension;

class ModCustom : public Layer, public ScrollViewDelegate
{
private:
    Layer* layer_top_;

//    Layer* layer_;
    ScrollView* layer_list_;
    std::vector<ModFoodShow*> food_;    //暂存食物列表
    Vec2 touch_began_;
    
    std::string food_list_; //存储食物的名字
    
    int reget_;
    
    EventListener* listener_;   //触控监听
#pragma mark - Initialization
public:
    ModCustom();
    ~ModCustom(){}
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(ModCustom);
    
public:
    
    void InitTop();
    void InitFood();
    
    void ButtonBackCallback(Ref* pSender, Widget::TouchEventType type);
    void ButtonInfoCallback(Ref* pSender, Widget::TouchEventType type);
    
    //触控回调
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual int AddListener();
    virtual void onTouchCancelled(Touch *touch, Event *event);
    
    void ScrollViewDidScroll(ScrollView* view);
    
#pragma mark - GetFood
    
    void GetFood();
    
    void ListCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    
    void GetList();
    
};

#endif /* defined(__MobileFoodOrderClient__mod_custom__) */
