//
//  mod_food_show.cpp
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/28/15.
//
//

#include "mod_food_show.h"

ModFoodShow::ModFoodShow():
food_id_(-1)
{
    
}

ModFoodShow::~ModFoodShow()
{
    
}

bool ModFoodShow::init()
{
    mod_http_->DownloadPicture(food_id_);
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto size = Director::getInstance()->getVisibleSize();
    
    this->setContentSize(Size(size.width, size.height / 5));
    
    auto* back_layer = LayerColor::create(Color4B(244, 245, 255, 255));
    back_layer->setContentSize(this->getContentSize());

    back_layer->setPosition(Vec2(origin.x, this->getPositionY()));
    addChild(back_layer,1);
    InitFoodShow();
//    this->scheduleUpdate();
    return true;
}

ModFoodShow* ModFoodShow::Create(int id)
{
    auto* ret = new ModFoodShow;
    ret->SetFoodId(id);
    if (ret && ret->init())
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

void ModFoodShow::update(float dt)
{
    if (0 == ModHttp::GetSocksDone())
    {
        ModHttp::SetGetSocksing();
        InitFoodShow();
    }
}

int ModFoodShow::InitFoodShow()
{
    log("init food show");
    
    auto path = FileUtils::getInstance()->getWritablePath() + "ceshi.jpg";
    img_ = Sprite::create(path);
    img_->setScale(this->getContentSize().height * 0.9 / img_->getContentSize().height );
    img_->setAnchorPoint(Vec2(0,0));
    img_->setPosition(Vec2(this->getContentSize().height * 0.05,
                           this->getContentSize().height * 0.05));
    addChild(img_,3);
    
    auto name = Label::createWithSystemFont("魅汁炒饭", "Arial", 24);
    name->setContentSize(Size(this->getContentSize().width * 2 / 3,
                              this->getContentSize().height * 1 / 4));
    name->setAnchorPoint(Vec2(0,0));
    name->setTextColor(Color4B(0,0,0,255));
    name->setPosition(Vec2(this->getContentSize().width * 2 / 5,
                           this->getContentSize().height * 3 / 4));
    addChild(name,3);
    
    auto button_info = Button::create("shop_button.png");
    button_info->setScale(this->getContentSize().width / (button_info->getContentSize().width * 6));
    button_info->setAnchorPoint(Vec2(0,0));
    button_info->setPosition(Vec2(this->getContentSize().width * 3 / 5,
                                  this->getContentSize().height * 1 / 5));
    addChild(button_info,3);
    
    auto button_shop = Button::create("info_button.png");
    button_shop->setScale(this->getContentSize().width / (button_shop->getContentSize().width * 6));
    button_shop->setAnchorPoint(Vec2(0,0));
    button_shop->setPosition(Vec2(this->getContentSize().width * 4 / 5,
                                  this->getContentSize().height * 1 / 5));
    addChild(button_shop,3);
    
    log("food show over");
    
    
    return 0;
}
