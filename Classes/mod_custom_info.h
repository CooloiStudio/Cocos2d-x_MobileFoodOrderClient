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
#include "cocos-ext.h"
#include "mod_shopping.h"
#include "mod_config_json.h"
#include "Info.h"

#include "json/document.h"
#include "json/rapidjson.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "network/HttpClient.h"

USING_NS_CC;
using namespace ui;
using namespace extension;

class ModCustomInfo : public Scene,
public extension::TableViewDataSource,
public extension::TableViewDelegate,
public EditBoxDelegate
{
private:
    LayerColor* layer_top_;
    LayerColor* layer_bottom_;
    
    extension::TableView* menu_;
    
    std::string get_into_;
    
    std::string address_;
    
    int table_num_;
    
    int reget_;
    
    int scene_info_;
    
    int id_;
    
#pragma mark - Initialization
public:
    ModCustomInfo(int info);
    ~ModCustomInfo(){}
    bool init();
    static Scene* createScene(int scene_info);
//    CREATE_FUNC(ModCustomInfo);
    
public:
    
    void InitTop();
    void ButtonBackCallback(Ref* pSender, Widget::TouchEventType type);
    void ButtonShopCallback(Ref* pSender, Widget::TouchEventType type);
    
    void InitMenu();
    
    void InitBottom();
    virtual void editBoxEditingDigBegin(EditBox* editbox);
    virtual void editBoxEditingDidEnd(EditBox* editbox);
    virtual void editBoxTextChanged (EditBox *editBox, const std::string &text);
    virtual void editBoxReturn (EditBox *editBox);
    void BottomShopCallback(Ref *psender, Widget::TouchEventType type);
    void SubmitShop();
    void SubmitShopCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    

    void UserLogOut();
    void LogOutCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    
    void GetInfo();
    void GetInfoCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    
    void SetSceneInfo(int scene_info);
    
#pragma mark - TableView
    
    void CreateTableView();
    virtual Size cellSizeForTable(extension::TableView* table);
    virtual extension::TableViewCell* tableCellAtIndex(extension::TableView* table,
                                                       ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(extension::TableView* table);
    virtual void tableCellTouched(extension::TableView* table,
                                  extension::TableViewCell* cell);
    virtual void scrollViewDidScroll(extension::ScrollView *view);
    
    
    void GetClientorder();
    void ClientorderCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void InitOrder();
    
    void CreateFoodOrder();
    
    void GetClientInfo();
    void ClientInfoCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    
};

#endif /* defined(__MobileFoodOrderClient__mod_custom_info__) */
