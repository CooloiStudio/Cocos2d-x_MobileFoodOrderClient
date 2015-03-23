//
//  mod_main_menu.h
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/15/15.
//
//

#ifndef __MobileFoodOrderClient__mod_main_menu__
#define __MobileFoodOrderClient__mod_main_menu__

#include "iostream"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "mod_custom.h"
#include "Info.h"

USING_NS_CC;
using namespace ui;
using namespace extension;

class ModMainMenu : public Layer,public EditBoxDelegate
{
private:
    
    int login_;//login = 0 为登陆，-1为注册
    
    std::string user_name_;
    std::string user_password_;
    std::string user_id_;
//    std::vector<EditBox* >box_;
    cocos2d::ui::EditBox* edit_name_;
    cocos2d::ui::EditBox* edit_pass_;
    cocos2d::ui::EditBox* edit_id_;
    
#pragma mark - Initialization
public:
    
    ModMainMenu();
    ~ModMainMenu();
    virtual bool init(int login);
    static Scene* createScene(int login);
    static Layer* LayerCreate(int login);
//    CREATE_FUNC(ModMainMenu);
    
public:
    void SetLogin(int login) {login_ = login;}
    
    
    void CreateEdit();
    virtual void editBoxEditingDigBegin(EditBox* editbox);
    virtual void editBoxEditingDidEnd(EditBox* editbox);
    virtual void editBoxTextChanged (EditBox *editBox, const std::string &text);
    virtual void editBoxReturn (EditBox *editBox);
    
    void CreateButton();
    void ButtonLoginCallback(Ref* pSender, Widget::TouchEventType type);
    
    void ButtonSignupCallback(Ref* pSender, Widget::TouchEventType type);
    
    void ButtonLogoutCallback(Ref* pSender, Widget::TouchEventType type);
    
    void ButtonCancelCallback(Ref* pSender, Widget::TouchEventType type);
    
    
    
};

#endif /* defined(__MobileFoodOrderClient__mod_main_menu__) */