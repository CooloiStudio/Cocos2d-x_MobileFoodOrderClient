//
//  mod_food_show.h
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/28/15.
//
//

#ifndef __MobileFoodOrderClient__mod_food_show__
#define __MobileFoodOrderClient__mod_food_show__

#include "iostream"
#include "cocos2d.h"
#include "mod_http.h"
#include "mod_check.h"
#include "cocos-ext.h"


#include "network/HttpClient.h"
#include "mod_config_json.h"

#include "json/document.h"
#include "json/rapidjson.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "network/HttpClient.h"

USING_NS_CC;
using namespace extension;
using namespace ui;
using namespace network;

class ModFoodShow : public Node
{
private:
    
    int food_id_;
    int is_network_done_;
    Sprite* img_;
    ModHttp* mod_http_;
    EventListener* listener_;
    
    std::string canteen_;
    std::string name_;
    std::string img_ad_;
    std::string description_;
    
public:
    void update(float dt);
    ModFoodShow(std::string food_info);
    ~ModFoodShow();
    bool init();
    static ModFoodShow* Create(int id, std::string food_info);
    
public:
    
#pragma mark - Interface
    
    void SetFoodId(int food_id){food_id_ = food_id;}
    int GetFoodId() {return food_id_;}
    
#pragma mark - Function
    
    int InitFoodShow();
    
    
    void ButtonShopCallback(Ref* pSender, Widget::TouchEventType type);
    
    void LogInCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    
    void GetList();
    
    
    int DownloadPicture();
    void OnDownloadComplete(HttpClient *sender, HttpResponse *response);
    
    
};

#endif /* defined(__MobileFoodOrderClient__mod_food_show__) */
