//
//  mod_food_info.cpp
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/29/15.
//
//

#include "mod_food_info.h"


ModFoodInfo::ModFoodInfo(std::string food):
reget_(0)
{
    rapidjson::Document d1;
    d1.Parse<0>(food.c_str());
    food_id_ = d1["id"].GetInt();
    canteen_ = d1["canteen"].GetString();
    name_ = d1["name"].GetString();
    img_ad_ = d1["img"].GetString();
    description_ = d1["description"].GetString();
    price_ = d1["price"].GetString();
}

ModFoodInfo::~ModFoodInfo()
{
    
}

ModFoodInfo* ModFoodInfo::CreateScene(std::string food)
{
    auto* ret = new ModFoodInfo(food);
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

bool ModFoodInfo::init()
{
    
    auto layer_background = LayerColor::create(Color4B(221,221,221,255));
    addChild(layer_background, 0);
    InitTop();
    InitFood();
    InitBottom();
    return true;
}

void ModFoodInfo::InitTop()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    auto size = Director::getInstance()->getVisibleSize();
    layer_top_ = LayerColor::create(Color4B(249, 249, 249, 255));
    layer_top_->setContentSize(Size(size.width,size.height / 15));
    layer_top_->setPosition(Vec2(origin.x + 0,origin.y + size.height / 15 * 14));
    layer_top_->setCascadeColorEnabled(true);
    //    layer_top_->setColor(Color3B(128,128,128));
    
    auto label_title = Label::createWithSystemFont(name_.c_str(), "Arial", 24);
    label_title->setDimensions(layer_top_->getContentSize().width / 4, layer_top_->getContentSize().height);
    label_title->setPosition(Vec2(layer_top_->getPositionX() + size.width / 2, layer_top_->getPositionY() + label_title->getContentSize().height / 2));
    label_title->setTextColor(Color4B(102,102,102,255));
    label_title->setAlignment(cocos2d::TextHAlignment::CENTER);
    label_title->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    
    
    auto button_back = Button::create("back.png");
    auto scale = layer_top_->getContentSize().height/ button_back->getContentSize().height * 0.8;
    button_back->setScale(scale);
    log("size %f",button_back->getContentSize().width );
    button_back->setPosition(Vec2(layer_top_->getPositionX() + button_back->getContentSize().width / 2 * scale, layer_top_->getPositionY() + layer_top_->getContentSize().height / 2));
    button_back->addTouchEventListener(CC_CALLBACK_2(ModFoodInfo::ButtonBackCallback, this));
    
    addChild(button_back,51);
//    addChild(button_info,51);
    addChild(label_title,51);
    addChild(layer_top_,50);

}

void ModFoodInfo::ButtonBackCallback(cocos2d::Ref *psender, Widget::TouchEventType type)
{
    Director::getInstance()->popScene();

}

void ModFoodInfo::ButtonInfoCallback(cocos2d::Ref *psender, Widget::TouchEventType type)
{
    
}

void ModFoodInfo::ButtonShopCallback(cocos2d::Ref *psender, Widget::TouchEventType type)
{
    
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            if (0 == LogInfo::GetLogIn())
                BuySomething();
            break;
            
        default:
            break;
    }
}

void ModFoodInfo::InitFood()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto size = Director::getInstance()->getVisibleSize();
    auto img_name_ = FileUtils::getInstance()->getWritablePath() + "food_" + custom_string::int_to_string(food_id_) + ".png";
    auto sprite = Sprite::create(  img_name_.c_str());
    sprite->setScale(size.width / (sprite->getContentSize().width * 1.5));
    sprite->setAnchorPoint(Vec2(0,0));
    sprite->setPosition(Vec2(origin.x + (size.width - sprite->getContentSize().width)/ 2,
                             origin.y + size.height - layer_top_->getContentSize().height - sprite->getContentSize().height - size.height / 20));
    addChild(sprite);
    
    auto labelprice = Label::createWithSystemFont("单价:", "Arial", 30);
    labelprice->setDimensions(sprite->getContentSize().width / 2, size.height / 15);
    labelprice->setAnchorPoint(Vec2(0,0));
    labelprice->setPosition(sprite->getPosition().x, sprite->getPosition().y - labelprice->getContentSize().height * 1.2);
    labelprice->setTextColor(Color4B(0,0,0,255));
    labelprice->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    labelprice->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    addChild(labelprice);
    
    auto price = Label::createWithSystemFont(price_.c_str(), "Arial", 30);
    price->setDimensions(sprite->getContentSize().width / 2, size.height / 15);
    price->setAnchorPoint(Vec2(0,0));
    price->setPosition(labelprice->getPosition().x + labelprice->getContentSize().width, labelprice->getPosition().y);
    price->setTextColor(Color4B(242,39,0,255));
    price->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    price->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    addChild(price);
    
    auto labelinfo = Label::createWithSystemFont("商品介绍:", "Arial", 30);
    labelinfo->setDimensions(sprite->getContentSize().width / 2, size.height / 15);
    labelinfo->setAnchorPoint(Vec2(0,0));
    labelinfo->setPosition(sprite->getPosition().x, sprite->getPosition().y - labelprice->getContentSize().height * 2.4);
    labelinfo->setTextColor(Color4B(0,0,0,255));
    labelinfo->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    labelinfo->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    addChild(labelinfo);
    
    auto info = Label::createWithSystemFont(description_.c_str(), "Arial", 30);
    info->setDimensions(sprite->getContentSize().width, size.height / 15 * 5);
    info->setAnchorPoint(Vec2(0, 1));
    info->setPosition(sprite->getPosition().x, sprite->getPosition().y - labelprice->getContentSize().height * 2.4);
    info->setTextColor(Color4B(0, 0, 0, 255));
    info->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    info->setVerticalAlignment(cocos2d::TextVAlignment::TOP);
    info->setLineBreakWithoutSpace(true);
    addChild(info);
    
    
}

void ModFoodInfo::InitBottom()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto size = Director::getInstance()->getVisibleSize();
    layer_bottom_ = LayerColor::create(Color4B(249, 249, 249, 255));
    layer_bottom_->setContentSize(Size(size.width,size.height / 15));
    layer_bottom_->setPosition(Vec2(origin.x ,origin.y));
    layer_bottom_->setCascadeColorEnabled(true);
    
//    auto label = Label::createWithSystemFont("数量： ", "Arial", 24);
//    label->setContentSize(Size(layer_bottom_->getContentSize().width / 5, size.height / 15));
//    label->setDimensions(layer_bottom_->getContentSize().width / 5, layer_bottom_->getContentSize().height);
//    label->setAnchorPoint(Vec2(0,0));
//    label->setPosition(Vec2(0,0));
//    label->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
//    label->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
//    label->setTextColor(Color4B(0,0,0,255));
//    
//    layer_bottom_->addChild(label);
//    
//    
//    auto edit = EditBox::create(Size(layer_bottom_->getContentSize().width / 4,layer_bottom_->getContentSize().height - 4), "edit.png");
//    edit->setAnchorPoint(Vec2(0,0));
//    edit->setPosition(Vec2(label->getPosition().x + label->getContentSize().width,2));
//    edit->setMaxLength(16);
//    edit->setFontColor(Color3B(0,0,0));
//    edit->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
//    //    edit_name_->setFontSize(24);
//    edit->setDelegate(this);
//    layer_bottom_->addChild(edit,1);
    
    auto shop = Button::create("foodshop.png");
    auto scale = layer_bottom_->getContentSize().height / shop->getContentSize().height;
    shop->setScale(scale);
    shop->setAnchorPoint(Vec2(0,0));
    shop->setPosition(Vec2(layer_bottom_->getContentSize().width - shop->getContentSize().width * scale, 0));
    shop->addTouchEventListener(CC_CALLBACK_2(ModFoodInfo::ButtonShopCallback, this));
    
    auto labelshop = Label::createWithSystemFont("加入购物车", "Arial", 24);
    labelshop->setTextColor(Color4B(255,255,255,255));
    labelshop->setDimensions(shop->getContentSize().width * scale, layer_bottom_->getContentSize().height);
    labelshop->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    labelshop->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    labelshop->setAnchorPoint(Vec2(0,0));
    labelshop->setPosition(shop->getPosition());
    
    layer_bottom_->addChild(shop);
    layer_bottom_->addChild(labelshop,2);
    
    addChild(layer_bottom_);
}


void ModFoodInfo::editBoxTextChanged(cocos2d::ui::EditBox *editBox, const std::string &text)
{
    num_ = text;
}

void ModFoodInfo::editBoxEditingDigBegin(cocos2d::ui::EditBox *editBox)
{
    
}

void ModFoodInfo::editBoxReturn(cocos2d::ui::EditBox *editBox)
{
    
}

void ModFoodInfo::editBoxEditingDidEnd(cocos2d::ui::EditBox *editbox)
{
    
}

void ModFoodInfo::BuySomething()
{
    auto path = FileUtils::getInstance()->getWritablePath() + "userinfo.json";
    
    auto user = FileUtils::getInstance()->getStringFromFile(path.c_str());
    
    HttpRequest *request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::POST);
    request->setTag("POST test");
    
    rapidjson::Document d1;
    rapidjson::Document::AllocatorType& allocator1 = d1.GetAllocator();
    d1.Parse<0>(user.c_str());
    
    
    d1.AddMember("food", food_id_, allocator1);
    
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
    d1.Accept(write);
    
    rapidjson::Document d;
    auto jsonpath = FileUtils::getInstance()->getWritablePath() + "config.json";
    auto jsonstr = FileUtils::getInstance()->getStringFromFile(jsonpath.c_str());
    d.Parse<0>(jsonstr.c_str());
    assert(d.IsObject());
    std::string ip = d["ip"].GetString();
    std::string port = d["port"].GetString();
    
    auto str = "http://" + ip + ":" + port + "/clientaddtoorder/";
    log("%s",buffer.GetString());
    
    request->setUrl(str.c_str());
    //    std::string str = "username=123&password=123";
    //    request->setRequestData(user.c_str(), user.size());
    request->setRequestData(buffer.GetString(), buffer.Size());
    
    request->setResponseCallback(CC_CALLBACK_2(ModFoodInfo::BuyCallback, this));
    
    HttpClient::getInstance()->send(request);
    request->release();
}

void ModFoodInfo::BuyCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
    if (!response) {
        return;
    }
    
    if (!response->isSucceed()) {
        CCLOG("error %s", response->getErrorBuffer());
        return;
    }
    
    //    response->getResponseDataString()
    
    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    //    _labelStatusCode->setString(statusString);
    log("response code: %d", statusCode);
    //    if (500 == statusCode)
    //    {
    //        UserLogIn();
    //        return;
    //    }
    
    if (500 == statusCode && 0 == ConfigJson::GetBoomNum() && 64 > reget_)
    {
        reget_++;
        BuySomething();
        return;
    }
    
    if (response->isSucceed())
    {
        std::string str = "";
        std::vector<char>* v = response->getResponseData();
        for (int i = 0; i < v->size(); i++)
        {
            //            printf("%c", v->at(i));
            str = str + v->at(i);
        }
        log("%s",str.c_str());
        printf("\n");
        
        rapidjson::Document d1;
        d1.Parse<0>(str.c_str());
        
        if (d1.HasParseError())
        {
            log("%s",d1.GetParseError());
            return;
        }
        
        assert(d1.IsObject());
        std::string test = "succeed";
        log ("%s",d1["response"].GetString());
        
        
        Director::getInstance()->replaceScene(ModCustomInfo::createScene(d1["order"]["id"].GetInt()));
        
    }
}




