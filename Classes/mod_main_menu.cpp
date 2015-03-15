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

Scene* ModMainMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = ModMainMenu::create();
    scene->addChild(layer);
    return scene;
}

bool ModMainMenu::init()
{
    CreateEdit();
    CreateButton();
    return true;
    
}

void ModMainMenu::CreateEdit()
{
    auto size = Director::getInstance()->getVisibleSize();
    edit_name_ = EditBox::create(Size(size.width * 0.3,size.height * 0.06 ), "bt.png");
    edit_name_->setPosition(Vec2(size.width / 2,size.height * 3 / 5));
    edit_name_->setMaxLength(16);
//    edit_name_->setFontSize(24);
    edit_name_->setDelegate(this);
    addChild(edit_name_);
    
    edit_pass_ = EditBox::create(Size(size.width * 0.3,size.height * 0.06 ), "bt.png");
    edit_pass_->setPosition(Vec2(size.width / 2,edit_name_->getPositionY() - edit_pass_->getContentSize().height * 2 ));
    edit_pass_->setMaxLength(16);
//    edit_pass_->setFontSize(24);
    edit_pass_->setDelegate(this);
    edit_pass_->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);
    addChild(edit_pass_);
    
    auto label_name = Label::createWithSystemFont("用户名:", "Airal", 20);
    label_name->setDimensions(size.width * 0.3,size.height * 0.06 );
    label_name->setAnchorPoint(Vec2(0.5, 0.5));
    label_name->setAlignment(cocos2d::TextHAlignment::LEFT);
    label_name->setVerticalAlignment(cocos2d::TextVAlignment::BOTTOM);
    label_name->setPosition(Vec2(edit_name_->getPositionX(),
                                 edit_name_->getPositionY() + edit_name_->getContentSize().height));
    addChild(label_name);
    
    auto label_pass = Label::createWithSystemFont("密码:", "Airal", 20);
    label_pass->setDimensions(size.width * 0.3,size.height * 0.06 );
    label_pass->setAnchorPoint(Vec2(0.5, 0.5));
    label_pass->setAlignment(cocos2d::TextHAlignment::LEFT);
    label_pass->setVerticalAlignment(cocos2d::TextVAlignment::BOTTOM);
    label_pass->setPosition(Vec2(edit_pass_->getPositionX(),
                                 edit_pass_->getPositionY() + edit_pass_->getContentSize().height));
    addChild(label_pass);

    
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
    auto login = Button::create("Confirm.png");
    auto signup = Button::create("pageup.png");
    auto logout = Button::create("Close.png");
    
    //登陆
    login->setPosition(Vec2(edit_pass_->getPositionX() - edit_pass_->getContentSize().width / 2 + login->getContentSize().width / 2,edit_pass_->getPositionY() - edit_pass_->getContentSize().height * 1.5));
    login->addTouchEventListener(CC_CALLBACK_2(ModMainMenu::ButtonLoginCallback, this));
    addChild(login,1);
    
    //注册
    signup->setPosition(Vec2(edit_pass_->getPositionX() + edit_pass_->getContentSize().width / 2 - signup->getContentSize().width / 2,edit_pass_->getPositionY() - edit_pass_->getContentSize().height * 1.5));
    signup->addTouchEventListener(CC_CALLBACK_2(ModMainMenu::ButtonLoginCallback, this));
    addChild(signup,1);
    
    //离开
    logout->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - logout->getContentSize().width,logout->getContentSize().height));
    logout->addTouchEventListener(CC_CALLBACK_2(ModMainMenu::ButtonLogoutCallback, this));
    addChild(logout,1);
    
    
}

void ModMainMenu::ButtonLoginCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
        {
            log("login");
            auto scene = ModCustom::createScene();
//            auto etc = TransitionMoveInL::create(1.0, scene);
            Director::getInstance()->pushScene(scene);
        }
            break;
        default:
            break;
    }
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




