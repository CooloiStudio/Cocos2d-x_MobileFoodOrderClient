//
//  mod_main_menu.cpp
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/15/15.
//
//

#include "mod_main_menu.h"

ModMainMenu::ModMainMenu()
{
    
}

ModMainMenu::~ModMainMenu()
{
    
}

Scene* ModMainMenu::createScene(int login)
{
    auto scene = Scene::create();
    auto layer = ModMainMenu::LayerCreate(login);
    scene->addChild(layer);
    return scene;
}

Layer* ModMainMenu::LayerCreate(int login)
{
    auto* ret = new ModMainMenu;
    if (ret && ret->init(login))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool ModMainMenu::init(int login)
{
    login_ = login;
    
    auto background = Sprite::create();
    background->setAnchorPoint(Vec2(0,0));
//    auto background = LayerColor::create(Color4B(240,240,255,255));
    if (login_ == 0)
        background->setTexture("bg.png");
    else
        background->setTexture("signbg.png");
    auto scale = Director::getInstance()->getVisibleSize().height / background->getContentSize().height ;
    auto action = ScaleBy::create(50,scale);
    
//    auto alv = Sprite::create("aalv.png");
//    auto alvscale = Director::getInstance()->getVisibleSize().width / (alv->getContentSize().width * 5);
//    alv->setPosition(Vec2(Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().width / 2 ,
//                          Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height / 5 * 4));
    //    alv->setScale(alvscale);
//    addChild(alv,1);
    background->runAction(action);
    background->setPosition(Vec2(Director::getInstance()->getVisibleOrigin().x,
                                 Director::getInstance()->getVisibleOrigin().y));
    addChild(background);
    
    CreateEdit();
    CreateButton();
    return true;
    
}

void ModMainMenu::CreateEdit()
{
    auto edit_back = LayerColor::create(Color4B(240,240,255,62));
//    edit_back->setContentSize(Size(Director::getInstance()->getVisibleSize().width / 2,
//                                   Director::getInstance()->getVisibleSize().height/ 2));
    edit_back->setAnchorPoint(Vec2(0.5,0.5));
    edit_back->setPosition(Vec2(Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().width / 2 - edit_back->getContentSize().width / 2,
                                Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height / 2 - edit_back->getContentSize().height / 2));
    this->addChild(edit_back);
    
    
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto size = Director::getInstance()->getVisibleSize();
    edit_name_ = EditBox::create(Size(size.width * 0.3,size.height * 0.06 ), "bt.png");
    edit_name_->setPosition(Vec2(origin.x + size.width / 2,origin.y + size.height * 3 / 5));
    edit_name_->setMaxLength(16);
    edit_name_->setFontColor(Color3B(0,0,0));
//    edit_name_->setFontSize(24);
    edit_name_->setDelegate(this);
    addChild(edit_name_,1);
    
    edit_pass_ = EditBox::create(Size(size.width * 0.3,size.height * 0.06 ), "bt.png");
    edit_pass_->setPosition(Vec2(origin.x + size.width / 2,origin.y + edit_name_->getPositionY() - edit_pass_->getContentSize().height * 1.5 ));
    edit_pass_->setMaxLength(16);
    edit_pass_->setFontColor(Color3B(0,0,0));
//    edit_pass_->setFontSize(24);
    edit_pass_->setDelegate(this);
    edit_pass_->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);
    addChild(edit_pass_,1);
    
    auto label_name = Label::createWithSystemFont("用户名:", "Airal", 20);
    label_name->setDimensions(edit_name_->getContentSize().width ,edit_name_->getContentSize().height  );
    label_name->setAnchorPoint(Vec2(0.5, 0.5));
    label_name->setAlignment(cocos2d::TextHAlignment::LEFT);
    label_name->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    label_name->setPosition(Vec2(origin.x + edit_name_->getPositionX() - label_name->getContentSize().width / 2,
                                 origin.y + edit_name_->getPositionY()));
    label_name->enableShadow();
    label_name->setTextColor(Color4B(240,240,255,255));
    addChild(label_name,1);
    
    auto label_pass = Label::createWithSystemFont("密码:", "Airal", 20);
    label_pass->setDimensions(edit_name_->getContentSize().width,edit_name_->getContentSize().height );
    label_pass->setAnchorPoint(Vec2(0.5, 0.5));
    label_pass->setAlignment(cocos2d::TextHAlignment::LEFT);
    label_pass->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    label_pass->setPosition(Vec2(origin.x + edit_pass_->getPositionX()  - label_pass->getContentSize().width / 2,
                                 origin.y + edit_pass_->getPositionY()));
    label_pass->enableShadow();
    label_pass->setTextColor(Color4B(240,240,255,255));
    addChild(label_pass,1);

    if (login_ == -1)
    {
        
        edit_id_ = EditBox::create(Size(size.width * 0.3,size.height * 0.06 ), "bt.png");
        edit_id_->setPosition(Vec2(origin.x + size.width / 2,origin.y + edit_name_->getPositionY() + edit_pass_->getContentSize().height * 1.5 ));
        edit_id_->setMaxLength(10);
        edit_id_->setFontColor(Color3B(0,0,0));
        //    edit_name_->setFontSize(24);
        edit_id_->setDelegate(this);
        addChild(edit_id_,1);
        
        auto label_id = Label::createWithSystemFont("学号:", "Airal", 20);
        label_id->setDimensions(edit_name_->getContentSize().width,edit_name_->getContentSize().height );
        label_id->setAnchorPoint(Vec2(0.5, 0.5));
        label_id->setAlignment(cocos2d::TextHAlignment::LEFT);
        label_id->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        label_id->setPosition(Vec2(origin.x + edit_id_->getPositionX()  - label_id->getContentSize().width / 2,
                                     origin.y + edit_id_->getPositionY()));
        label_id->enableShadow();
        label_id->setTextColor(Color4B(240,240,255,255));
        addChild(label_id,1);

    }
    
}

void ModMainMenu::editBoxEditingDigBegin(cocos2d::ui::EditBox *editBox)
{
    
}

void ModMainMenu::editBoxEditingDidEnd(cocos2d::ui::EditBox *editBox)
{
    
}

void ModMainMenu::editBoxTextChanged(cocos2d::ui::EditBox *editBox, const std::string &text)
{
    if (editBox == edit_name_)
    {
        user_name_ = text;
    }
    if (editBox == edit_pass_)
    {
        user_password_ = text;
    }
}

void ModMainMenu::editBoxReturn(cocos2d::ui::EditBox* editBox)
{
    
}

void ModMainMenu::CreateButton()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto size = Director::getInstance()->getVisibleSize();
    auto signup = Button::create("signup.png");
    auto scale = Director::getInstance()->getVisibleSize().width / (signup->getContentSize().width * 8);
    
    if (login_ == 0)
    {
    auto login = Button::create("login.png");
    auto logout = Button::create("close.png");
    //登陆
    login->setScale(scale);
    login->setAnchorPoint(Vec2(0.5,0.5));
    login->setPosition(Vec2(origin.x + size.width * 4/10 ,
                            origin.y + edit_pass_->getPositionY() - edit_pass_->getContentSize().height * 1.5));
    login->addTouchEventListener(CC_CALLBACK_2(ModMainMenu::ButtonLoginCallback, this));
    addChild(login,1);
    
    //注册
    signup->setScale(scale);
    signup->setAnchorPoint(Vec2(0.5,0.5));
    signup->setPosition(Vec2(origin.x + size.width * 6/10 ,
                             origin.y + edit_pass_->getPositionY() - edit_pass_->getContentSize().height * 1.5));
    signup->addTouchEventListener(CC_CALLBACK_2(ModMainMenu::ButtonSignupCallback, this));
    addChild(signup,1);
    
    //离开
    logout->setPosition(Vec2(origin.x + Director::getInstance()->getVisibleSize().width - logout->getContentSize().width,origin.y + logout->getContentSize().height));
    logout->addTouchEventListener(CC_CALLBACK_2(ModMainMenu::ButtonLogoutCallback, this));
    addChild(logout,1);
    }
    else
    {
        auto cancel = Button::create("cancel.png");
        
        
        signup->setScale(scale);
        signup->setAnchorPoint(Vec2(0.5,0.5));
        signup->setPosition(Vec2(origin.x + size.width * 4/10 ,
                                origin.y + edit_pass_->getPositionY() - edit_pass_->getContentSize().height * 1.5));
        signup->addTouchEventListener(CC_CALLBACK_2(ModMainMenu::ButtonLoginCallback, this));
        addChild(signup,1);
        
        
        cancel->setScale(scale);
        cancel->setAnchorPoint(Vec2(0.5,0.5));
        cancel->setPosition(Vec2(origin.x + size.width * 6/10 ,
                                 origin.y + edit_pass_->getPositionY() - edit_pass_->getContentSize().height * 1.5));
        cancel->addTouchEventListener(CC_CALLBACK_2(ModMainMenu::ButtonCancelCallback, this));
        addChild(cancel,1);
        
    }
    
}

void ModMainMenu::ButtonLoginCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
        {
            LogInfo::SetLogIn();
            log("login");
            auto* scene = ModCustom::createScene();
            auto etc = TransitionMoveInR::create(0.5, scene);
            Director::getInstance()->pushScene(etc);
        }
            break;
        default:
            break;
    }
}

void ModMainMenu::ButtonCancelCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
    Director::getInstance()->popScene();
}

void ModMainMenu::ButtonSignupCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
    Director::getInstance()->pushScene(createScene(-1));
}


void ModMainMenu::ButtonLogoutCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}




