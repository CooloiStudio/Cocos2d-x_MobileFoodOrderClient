//
//  mod_custom_info.cpp
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/15/15.
//
//

#include "mod_custom_info.h"
#include "mod_custom.h"

ModCustomInfo::ModCustomInfo(int info):
reget_(20),
scene_info_(info)
{
    
}

bool ModCustomInfo::init()
{
    auto layer_background = LayerColor::create(Color4B(240,240,255,255));
    addChild(layer_background);
    InitTop();
    if (0 == scene_info_)
        GetInfo();
    if (-1 == scene_info_)
        GetClientorder();
    if (0 < scene_info_)
    {
        GetClientInfo();
    }
    return true;
}

Scene* ModCustomInfo::createScene(int info)
{
    auto* ret = new ModCustomInfo(info);
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

void ModCustomInfo::InitTop()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto size = Director::getInstance()->getVisibleSize();
    layer_top_ = LayerColor::create(Color4B(244, 245, 255, 255));
    layer_top_->setContentSize(Size(size.width,size.height / 15));
    layer_top_->setPosition(Vec2(origin.x + 0,origin.y + size.height / 15 * 14));
    layer_top_->setCascadeColorEnabled(true);
    //    layer_top_->setColor(Color3B(128,128,128));
    
    auto label_title = Label::createWithSystemFont("我的信息", "Arial", 24);
    
    if (-1 == scene_info_)
        label_title->setString("订单信息");
    
    if (0 < scene_info_)
        label_title->setString("订单详情");
    label_title->setDimensions(layer_top_->getContentSize().width / 4, layer_top_->getContentSize().height);
    label_title->setPosition(Vec2(layer_top_->getPositionX() + size.width / 2,layer_top_->getPositionY() + label_title->getContentSize().height / 2));
    label_title->setTextColor(Color4B(102,102,102,255));
    label_title->setAlignment(cocos2d::TextHAlignment::CENTER);
    label_title->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    
    
    auto button_back = Button::create("back.png");
    auto scale = layer_top_->getContentSize().height/ button_back->getContentSize().height * 0.8;
    button_back->setScale(scale);
    log("size %f",button_back->getContentSize().width );
    button_back->setPosition(Vec2(layer_top_->getPositionX() + button_back->getContentSize().width / 2 * scale,layer_top_->getPositionY() + layer_top_->getContentSize().height / 2));
    button_back->addTouchEventListener(CC_CALLBACK_2(ModCustomInfo::ButtonBackCallback, this));
    
//    auto button_shop = Button::create("shop.png");
//    button_shop->setScale(scale);
//    button_shop->setPosition(Vec2(layer_top_->getPositionX() + size.width - button_back->getContentSize().width / 2 * scale,layer_top_->getPositionY() + layer_top_->getContentSize().height / 2));
//    button_shop->addTouchEventListener(CC_CALLBACK_2(ModCustomInfo::ButtonShopCallback, this));
    
    
    addChild(button_back,2);
//    addChild(button_shop,2);
    addChild(label_title,2);
    addChild(layer_top_,1);
}

void InitButton()
{
    auto size = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto sprite = Sprite::create();
    sprite->setTextureRect(Rect(0,0,size.width, size.height / 6));
    sprite->setColor(Color3B(255,255,255));

    
}

void ModCustomInfo::ButtonShopCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
//    UserLogOut();
//    GetInfo();
    
    Director::getInstance()->replaceScene(ModCustomInfo::createScene(-1));
//    auto* ret = ModShopping::createScene();
//    Director::getInstance()->pushScene(ret);
}

void ModCustomInfo::ButtonBackCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
//    Director::getInstance()->popScene();
    Director::getInstance()->replaceScene(ModCustom::createScene());
}

void ModCustomInfo::LogOutCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
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
    if (500 == statusCode && 0 == ConfigJson::GetBoomNum() && 32 > reget_)
    {
        reget_++;
        UserLogOut();
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
        
//        rapidjson::StringBuffer buffer;
//        rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
//        game_log.Accept(write);
//        log("InitLog is %s",buffer.GetString());
//        
//        std::string path = FileUtils::getInstance()->getWritablePath() + "GameLog.json";
//        FILE* file = fopen(path.c_str(), "wb");
//        if(file) {
//            fputs(buffer.GetString(), file);
//            fclose(file);
//        }
        
        
    }
    
    
    
}
void ModCustomInfo::UserLogOut()
{
    log("GET");
    HttpRequest *request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::GET);
    request->setTag("POST test");
    
    rapidjson::Document d;
    auto jsonpath = FileUtils::getInstance()->getWritablePath() + "config.json";
    auto jsonstr = FileUtils::getInstance()->getStringFromFile(jsonpath.c_str());
    d.Parse<0>(jsonstr.c_str());
    assert(d.IsObject());
    std::string ip = d["ip"].GetString();
    std::string port = d["port"].GetString();
    
    auto str = "http://" + ip + ":" + port + "/clientlogout/";
    
    request->setUrl(str.c_str());
//    std::string str = "username=123&password=123";
    //    request->setRequestData(str.c_str(), str.size());
    
    
    
    request->setResponseCallback(CC_CALLBACK_2(ModCustomInfo::LogOutCallback, this));
    HttpClient::getInstance()->send(request);
    request->release();
}

void ModCustomInfo::GetInfoCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
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
    if (500 == statusCode && 0 == ConfigJson::GetBoomNum() && 32 > reget_)
    {
        reget_++;
//        UserLogOut();
        GetInfo();
        return;
    }
    
    if (response->isSucceed())
    {
//        std::string str = "";
        
        std::vector<char>* v = response->getResponseData();
        for (int i = 0; i < v->size(); i++)
        {
            //            printf("%c", v->at(i));
            get_into_ = get_into_ + v->at(i);
        }
        log("%s",get_into_.c_str());
        printf("\n");
        
//        Director::getInstance()->replaceScene(ModCustomInfo::createScene(-1));
//        getLights();
        CreateTableView();
    }
    
    
    
}
void ModCustomInfo::GetInfo()
{
    log("Get Info");
    auto path = FileUtils::getInstance()->getWritablePath() + "userinfo.json";
    
    auto user = FileUtils::getInstance()->getStringFromFile(path.c_str());
    
    HttpRequest *request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::POST);
    request->setTag("POST test");
    
    rapidjson::Document d;
    auto jsonpath = FileUtils::getInstance()->getWritablePath() + "config.json";
    auto jsonstr = FileUtils::getInstance()->getStringFromFile(jsonpath.c_str());
    d.Parse<0>(jsonstr.c_str());
    assert(d.IsObject());
    std::string ip = d["ip"].GetString();
    std::string port = d["port"].GetString();
    
    auto str = "http://" + ip + ":" + port + "/clientuserinfo/";
    
    request->setUrl(str.c_str());
    //    std::string str = "username=123&password=123";
        request->setRequestData(user.c_str(), user.size());
    
    log("Get Info is %s",user.c_str());
    
    request->setResponseCallback(CC_CALLBACK_2(ModCustomInfo::GetInfoCallback, this));
    HttpClient::getInstance()->send(request);
    request->release();
}



///////////////////


void ModCustomInfo::InitMenu()
{
    
    
    rapidjson::Document d1;
    d1.Parse<0>(get_into_.c_str());
    
    if (d1.HasParseError())
    {
        log("%s",d1.GetParseError());
        return;
    }
    
    assert(d1.IsObject());
    
    //        rapidjson::StringBuffer buffer;
    //        rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
    //        game_log.Accept(write);
    //        log("InitLog is %s",buffer.GetString());
    //
    //        std::string path = FileUtils::getInstance()->getWritablePath() + "GameLog.json";
    //        FILE* file = fopen(path.c_str(), "wb");
    //        if(file) {
    //            fputs(buffer.GetString(), file);
    //            fclose(file);
    //        }
}

void ModCustomInfo::InitBottom()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto size = Director::getInstance()->getVisibleSize();
    layer_bottom_ = LayerColor::create(Color4B(249, 249, 249, 255));
    layer_bottom_->setContentSize(Size(size.width,size.height / 15));
    layer_bottom_->setPosition(Vec2(origin.x ,origin.y));
    layer_bottom_->setCascadeColorEnabled(true);
    
        auto label = Label::createWithSystemFont("收货地址", "Arial", 22);
        label->setContentSize(Size(layer_bottom_->getContentSize().width / 5, size.height / 15));
        label->setDimensions(layer_bottom_->getContentSize().width / 5, layer_bottom_->getContentSize().height);
        label->setAnchorPoint(Vec2(0,0));
        label->setPosition(Vec2(0,0));
        label->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
        label->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        label->setTextColor(Color4B(0,0,0,255));
    
        layer_bottom_->addChild(label);
    
    
        auto edit = EditBox::create(Size(layer_bottom_->getContentSize().width / 4,layer_bottom_->getContentSize().height - 4), "edit.png");
        edit->setAnchorPoint(Vec2(0,0));
        edit->setPosition(Vec2(label->getPosition().x + label->getContentSize().width,2));
        edit->setMaxLength(16);
        edit->setFontColor(Color3B(0,0,0));
//        edit->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
        //    edit_name_->setFontSize(24);
        edit->setDelegate(this);
        layer_bottom_->addChild(edit,1);
    
    auto shop = Button::create("foodshop.png");
    auto scale = layer_bottom_->getContentSize().height / shop->getContentSize().height;
    shop->setScale(scale);
    shop->setAnchorPoint(Vec2(0,0));
    shop->addTouchEventListener(CC_CALLBACK_2(ModCustomInfo::BottomShopCallback, this));
    shop->setPosition(Vec2(layer_bottom_->getContentSize().width - shop->getContentSize().width * scale, 0));
    
    auto labelshop = Label::createWithSystemFont("确认订单", "Arial", 24);
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

void ModCustomInfo::BottomShopCallback(cocos2d::Ref *psender, Widget::TouchEventType type)
{
    if (2 < address_.size())
    {
        SubmitShop();
    }
}

void ModCustomInfo::SubmitShop()
{
    log("Get Info");
    auto path = FileUtils::getInstance()->getWritablePath() + "userinfo.json";
    
    auto user = FileUtils::getInstance()->getStringFromFile(path.c_str());
    
//    
//    rapidjson::Document d2;
//    d2.Parse<0>(get_into_.c_str());
//    int strid = d2["order"]["id"].GetInt();
    
    rapidjson::Document d1;
    rapidjson::Document::AllocatorType& allocator = d1.GetAllocator();
    d1.Parse<0>(user.c_str());
    
    d1.AddMember("address", address_.c_str(), allocator);
//    d1.AddMember("order_id", custom_string::int_to_string(id_).c_str(), allocator);
    d1.AddMember("order_id", id_, allocator);

    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
    d1.Accept(write);
    
    
    
    HttpRequest *request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::POST);
    request->setTag("POST test");
    
    rapidjson::Document d;
    auto jsonpath = FileUtils::getInstance()->getWritablePath() + "config.json";
    auto jsonstr = FileUtils::getInstance()->getStringFromFile(jsonpath.c_str());
    d.Parse<0>(jsonstr.c_str());
    assert(d.IsObject());
    std::string ip = d["ip"].GetString();
    std::string port = d["port"].GetString();
    
    auto str = "http://" + ip + ":" + port + "/clientorderconfirm/";
    log("%s",buffer.GetString());
    request->setUrl(str.c_str());
    //    std::string str = "username=123&password=123";
    request->setRequestData(buffer.GetString(), buffer.Size());
    
    
    
    request->setResponseCallback(CC_CALLBACK_2(ModCustomInfo::SubmitShopCallback, this));
    HttpClient::getInstance()->send(request);
    request->release();
}

void ModCustomInfo::SubmitShopCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
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
    
    if (500 == statusCode && 0 == ConfigJson::GetBoomNum() && 32 > reget_)
    {
        reget_++;
        SubmitShop();
        return;
    }
    if (404 == statusCode)
        return;
    
    if (response->isSucceed())
    {
        get_into_ = "";
        
        
        std::vector<char>* v = response->getResponseData();
        for (int i = 0; i < v->size(); i++)
        {
            //            printf("%c", v->at(i));
            get_into_ = get_into_ + v->at(i);
        }
        log("%s",get_into_.c_str());
        printf("\n");
        
        rapidjson::Document d1;
        d1.Parse<0>(get_into_.c_str());
        
        if (d1.HasParseError())
        {
            log("%s",d1.GetParseError());
            return;
        }
        
        assert(d1.IsObject());
        std::string test = "succeed";
        log ("submit is and %s",d1["response"].GetString());
        
        
        Director::getInstance()->replaceScene(ModCustomInfo::createScene(id_));
//        CreateFoodOrder();
//        CreateTableView();
        
        
    }

}

void ModCustomInfo::editBoxTextChanged(cocos2d::ui::EditBox *editBox, const std::string &text)
{
    address_ = text;
}

void ModCustomInfo::editBoxEditingDigBegin(cocos2d::ui::EditBox *editBox)
{
    
}

void ModCustomInfo::editBoxReturn(cocos2d::ui::EditBox *editBox)
{
    
}

void ModCustomInfo::editBoxEditingDidEnd(cocos2d::ui::EditBox *editbox)
{
    
}

void ModCustomInfo::CreateFoodOrder()
{
    
    auto size = Director::getInstance()->getVisibleSize();
    
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto bg_color = Color3B(244, 245, 255);
    
    auto bg = Layer::create();
    auto bg_sprite = Sprite::create();
    bg_sprite->setAnchorPoint(Vec2(0,0));
    bg_sprite->setTextureRect(Rect(0, 0, size.width, size.height / 6 - 2));
    bg_sprite->setColor(bg_color);
    bg_sprite->setPosition(Vec2(origin.x , origin.y + size.height - layer_top_->getContentSize().height - bg_sprite->getContentSize().height));
    bg->addChild(bg_sprite);
    addChild(bg);
    
    
    auto id = Label::createWithSystemFont("订单编号： ", "Arial", 24);
    //        label->setContentSize(Size( size.width / 2, size.height / 10));
    id->setDimensions( size.width, size.height / 6);
    id->setTextColor(Color4B(0,0,0,255));
    id->setAnchorPoint(Vec2(0,0));
    id->setAlignment(cocos2d::TextHAlignment::LEFT);
    id->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    id->setPosition(Vec2(bg_sprite->getPosition().x + size.width / 12, bg_sprite->getPosition().y + (size.height / 6 - 2 ) / 6 * 2));
    
    bg->addChild(id);
    
    rapidjson::Document d1;
    d1.Parse<0>(get_into_.c_str());
    
    
    int strid = d1["order"]["id"].GetInt();
    id_ = d1["order"]["id"].GetInt();
    auto label_id = Label::createWithSystemFont(custom_string::int_to_string(strid).c_str(), "Arial", 24);
    
    //        label->setContentSize(Size( size.width / 2, size.height / 10));
    label_id->setDimensions( size.width, size.height / 6);
    label_id->setTextColor(Color4B(0,0,0,255));
    label_id->setAnchorPoint(Vec2(0,0));
    label_id->setAlignment(cocos2d::TextHAlignment::LEFT);
    label_id->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    label_id->setPosition(Vec2(bg_sprite->getPosition().x + size.width / 3,bg_sprite->getPosition().y +   (size.height / 6 - 2 ) / 6 * 2));
    
    bg->addChild(label_id);
    
    auto price = Label::createWithSystemFont("订单金额： ", "Arial", 24);
    //        label->setContentSize(Size( size.width / 2, size.height / 10));
    price->setDimensions( size.width, size.height / 6);
    price->setTextColor(Color4B(0,0,0,255));
    price->setAnchorPoint(Vec2(0,0));
    price->setAlignment(cocos2d::TextHAlignment::LEFT);
    price->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    price->setPosition(Vec2(bg_sprite->getPosition().x + size.width / 12,bg_sprite->getPosition().y +  (size.height / 6 - 2 ) / 6 ));
    
    bg->addChild(price);
    
    auto str = d1["order"]["price"].GetString();
    auto label_price = Label::createWithSystemFont(str, "Arial", 24);
    //        label->setContentSize(Size( size.width / 2, size.height / 10));
    label_price->setDimensions( size.width, size.height / 6);
    label_price->setTextColor(Color4B(0,0,0,255));
    label_price->setAnchorPoint(Vec2(0,0));
    label_price->setAlignment(cocos2d::TextHAlignment::LEFT);
    label_price->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    label_price->setPosition(Vec2(bg_sprite->getPosition().x + size.width / 3,bg_sprite->getPosition().y +  (size.height / 6 - 2 ) / 6 ));
    
    bg->addChild(label_price);
    
    
    auto label = Label::createWithSystemFont("交易状态： ", "Arial", 24);
    //        label->setContentSize(Size( size.width / 2, size.height / 10));
    label->setDimensions( size.width, size.height / 6);
    label->setTextColor(Color4B(0,0,0,255));
    label->setAnchorPoint(Vec2(0,0));
    label->setAlignment(cocos2d::TextHAlignment::LEFT);
    label->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    label->setPosition(Vec2(bg_sprite->getPosition().x + size.width / 12,bg_sprite->getPosition().y +  0));
    
    bg->addChild(label);
    

    
    auto label_buff = Label::createWithSystemFont("", "Arial", 24);
    std::string suc = d1["order"]["confirm"].GetString();
    str = "未确定";
    if ("True" == suc)
    {
        str = "派送中";
    }
    else
    {
//        label_buff->setTextColor(Color4B(242,39,0,255));
//        auto edit = EditBox::create(Size(size.width / 2,size.height / 36 * 2), "edit.png");
//        edit->setAnchorPoint(Vec2(0,0));
//        edit->setPosition(Vec2(label->getPosition().x + label->getContentSize().width,2));
//        edit->setMaxLength(16);
//        edit->setFontColor(Color3B(0,0,0));
//        //        edit->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
//        //    edit_name_->setFontSize(24);
//        edit->setDelegate(this);
//        bg->addChild(edit,1);
//        
//        auto shop = Button::create("foodshop.png");
//        auto scale = size.width / (shop->getContentSize().width * 3);
//        shop->setScale(scale);
//        shop->setAnchorPoint(Vec2(0,0));
//        shop->addTouchEventListener(CC_CALLBACK_2(ModCustomInfo::BottomShopCallback, this));
//        shop->setPosition(Vec2(bg_sprite->getPosition().x + size.width - shop->getContentSize().width, bg_sprite->getPosition().y + 0));
//                shop->setPosition(Vec2(0, 0));
//        
//        auto labelshop = Label::createWithSystemFont("确认订单", "Arial", 24);
//        labelshop->setTextColor(Color4B(255,255,255,255));
//        labelshop->setDimensions(shop->getContentSize().width * scale, shop->getContentSize().height * scale);
//        labelshop->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
//        labelshop->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
//        labelshop->setAnchorPoint(Vec2(0,0));
//        labelshop->setPosition(shop->getPosition());
//        
//        bg->addChild(shop);
//        bg->addChild(labelshop,2);
        InitBottom();
    }
    suc = d1["order"]["deal"].GetString();
    if ("True" == suc)
        str = "交易已完成";
    
    label_buff->setString(str);
    //        label->setContentSize(Size( size.width / 2, size.height / 10));
    label_buff->setDimensions( size.width, size.height / 6);
    label_buff->setTextColor(Color4B(0,0,0,255));
    label_buff->setAnchorPoint(Vec2(0,0));
    label_buff->setAlignment(cocos2d::TextHAlignment::LEFT);
    label_buff->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    label_buff->setPosition(Vec2(bg_sprite->getPosition().x + size.width / 3,bg_sprite->getPosition().y +  0));
    
    bg->addChild(label_buff);
    
    auto address = Label::createWithSystemFont("送货地址： ", "Arial", 24);
    //        label->setContentSize(Size( size.width / 2, size.height / 10));
    address->setDimensions( size.width, size.height / 6);
    address->setTextColor(Color4B(0,0,0,255));
    address->setAnchorPoint(Vec2(0,0));
    address->setAlignment(cocos2d::TextHAlignment::LEFT);
    address->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    address->setPosition(Vec2(bg_sprite->getPosition().x + size.width / 12,bg_sprite->getPosition().y +  -(size.height / 6 - 2 ) / 6 ));
    
    bg->addChild(address);
    
    
    str = d1["order"]["address"].GetString();
    auto label_address = Label::createWithSystemFont(str, "Arial", 24);
    //        label->setContentSize(Size( size.width / 2, size.height / 10));
    label_address->setDimensions( size.width, size.height / 6);
    label_address->setTextColor(Color4B(0,0,0,255));
    label_address->setAnchorPoint(Vec2(0,0));
    label_address->setAlignment(cocos2d::TextHAlignment::LEFT);
    label_address->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    label_address->setPosition(Vec2(bg_sprite->getPosition().x + size.width / 3,bg_sprite->getPosition().y +  -(size.height / 6 - 2 ) / 6 ));
    
    bg->addChild(label_address);
    
    auto time = Label::createWithSystemFont("交易时间： ", "Arial", 24);
    //        label->setContentSize(Size( size.width / 2, size.height / 10));
    time->setDimensions( size.width, size.height / 6);
    time->setTextColor(Color4B(0,0,0,255));
    time->setAnchorPoint(Vec2(0,0));
    time->setAlignment(cocos2d::TextHAlignment::LEFT);
    time->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    time->setPosition(Vec2(bg_sprite->getPosition().x + size.width / 12,bg_sprite->getPosition().y +  -(size.height / 6 - 2 ) / 6 * 2));
    
    bg->addChild(time);
    
    str = d1["order"]["time"].GetString();
    auto label_time = Label::createWithSystemFont(str, "Arial", 24);
    //        label->setContentSize(Size( size.width / 2, size.height / 10));
    label_time->setDimensions( size.width, size.height / 6);
    label_time->setTextColor(Color4B(0,0,0,255));
    label_time->setAnchorPoint(Vec2(0,0));
    label_time->setAlignment(cocos2d::TextHAlignment::LEFT);
    label_time->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    label_time->setPosition(Vec2(bg_sprite->getPosition().x + size.width / 3,bg_sprite->getPosition().y +  -(size.height / 6 - 2 ) / 6 * 2));
    
    bg->addChild(label_time);
}

void ModCustomInfo::CreateTableView()
{
    auto size = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    if (0 < scene_info_)
        menu_ = extension::TableView::create(this, Size(Size(size.width, size.height - size.height / 15 - size.height / 6)));
    else
        menu_ = extension::TableView::create(this, Size(Size(size.width, size.height - size.height / 15)));
    menu_->setPosition(Vec2(origin.x, origin.y + size.height / 15));
    //        menu_->setPosition(Vec2(origin.x + size.width / 4, origin.y));
    menu_->setViewSize(Size(menu_->getViewSize().width, menu_->getViewSize().height - size.height / 15));
    menu_->setBounceable(true);
    menu_->setDirection(extension::ScrollView::Direction::VERTICAL);
    menu_->setVerticalFillOrder(extension::TableView::VerticalFillOrder::TOP_DOWN);
    menu_->setDelegate(this);
    addChild(menu_);
    menu_->reloadData();
    
    
}



//table's size
Size ModCustomInfo::cellSizeForTable(extension::TableView *table)
{
    auto size = Director::getInstance()->getVisibleSize();
    return Size(size.width , size.height / 6 );
}

//num of table
ssize_t ModCustomInfo::numberOfCellsInTableView(extension::TableView *table)
{
    rapidjson::Document d1;
    d1.Parse<0>(get_into_.c_str());
    
    if (d1.HasParseError())
    {
        log("%s",d1.GetParseError());
        return 0 ;
    }
    
    assert(d1.IsObject());
//
//    rapidjson::Value& user = d1["user"];
//    
//    
//    //        rapidjson::StringBuffer buffer;
//    //        rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
//    //        game_log.Accept(write);
//    //        log("InitLog is %s",buffer.GetString());
//    //
//    //        std::string path = FileUtils::getInstance()->getWritablePath() + "GameLog.json";
//    //        FILE* file = fopen(path.c_str(), "wb");
//    //        if(file) {
//    //            fputs(buffer.GetString(), file);
//    //            fclose(file);
//    //        }
//    table_num_ = user.Size() - 2;
    if (-1 == scene_info_)
    {
        assert (d1["order"].IsArray());
//        log("%d",d1["order"].Size());
        return d1["order"].Size();
    }
    
    if (0 < scene_info_)
    {
        return d1["food"].Size();
//        return 0;
    }
    
    return 3;
}

extension::TableViewCell* ModCustomInfo::tableCellAtIndex(extension::TableView *table,
                                                  ssize_t idx)
{
    rapidjson::Document d1;
    d1.Parse<0>(get_into_.c_str());
    
    if (d1.HasParseError())
    {
        log("%s",d1.GetParseError());
        return 0 ;
    }
    
    
    auto size = Director::getInstance()->getVisibleSize();
    extension::TableViewCell* cell = table->dequeueCell();
    cell = new extension::TableViewCell;
    cell->autorelease();
    
    auto bg_color = Color3B(244, 245, 255);
    
    auto bg_sprite = Sprite::create();
    bg_sprite->setAnchorPoint(Vec2(0,0));
    bg_sprite->setTextureRect(Rect(0, 0, size.width, size.height / 6 - 2));
    bg_sprite->setColor(bg_color);
    cell->addChild(bg_sprite);
    
    if (0 < scene_info_)
    {
        
        auto path = FileUtils::getInstance()->getWritablePath() + "food_" + custom_string::int_to_string(d1["food"][idx]["id"].GetInt()) + ".png";

        auto img_ = Sprite::create(path.c_str());
        img_->setScale(size.height / 6 * 0.9 / img_->getContentSize().height );
        img_->setAnchorPoint(Vec2(0,0));
        img_->setPosition(Vec2(this->getContentSize().height * 0.05,
                               this->getContentSize().height * 0.05));
        cell->addChild(img_);
        
        auto name = Label::createWithSystemFont(d1["food"][idx]["name"].GetString(), "Arial", 24);
        name->setDimensions(this->getContentSize().width / 4,
                            size.height / 6);
        name->setAnchorPoint(Vec2(0,0));
        name->setTextColor(Color4B(0,0,0,255));
        name->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
        name->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        name->setPosition(Vec2(size.width / 3,
                               (size.height / 6 - 2 ) / 6 * 2));
        cell->addChild(name,3);
        
        auto label_price = Label::createWithSystemFont("单价：", "Arial", 24);
        label_price->setDimensions(this->getContentSize().width / 4,
                               size.height / 6);
        label_price->setAnchorPoint(Vec2(0,0));
        label_price->setTextColor(Color4B(0, 0, 0,255));
        label_price->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
        label_price->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        label_price->setPosition(Vec2(size.width / 3 , 0));
        cell->addChild(label_price,3);
        
        auto price = Label::createWithSystemFont(d1["food"][idx]["price"].GetString(), "Arial", 24);
        price->setDimensions(this->getContentSize().width / 4,
                            size.height / 6);
        price->setAnchorPoint(Vec2(0,0));
        price->setTextColor(Color4B(242, 39, 0,255));
        price->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
        price->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        price->setPosition(Vec2(size.width / 3 * 2, 0));
        cell->addChild(price,3);
        
        auto label_centeen = Label::createWithSystemFont("派送单位：", "Arial", 24);
        label_centeen->setDimensions(this->getContentSize().width / 4,
                                   size.height / 6);
        label_centeen->setAnchorPoint(Vec2(0,0));
        label_centeen->setTextColor(Color4B(0, 0, 0,255));
        label_centeen->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
        label_centeen->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        label_centeen->setPosition(Vec2(size.width / 3 , -(size.height / 6 - 2 ) / 6 * 2));
        cell->addChild(label_centeen,3);
        
        auto centeen = Label::createWithSystemFont(d1["food"][idx]["canteen"].GetString(), "Arial", 24);
        centeen->setDimensions(this->getContentSize().width / 4,
                             size.height / 6);
        centeen->setAnchorPoint(Vec2(0,0));
        centeen->setTextColor(Color4B(0, 0, 0,255));
        centeen->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
        centeen->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        centeen->setPosition(Vec2(size.width / 3 * 2, -(size.height / 6 - 2 ) / 6 * 2));
        cell->addChild(centeen,3);
        
//        auto label_price = Label::createWithSystemFont("单价：", "Arial", 24);
//        label_price->setDimensions(this->getContentSize().width / 4,
//                                   this->getContentSize().height * 1 / 4);
//        label_price->setAnchorPoint(Vec2(0,0));
//        label_price->setTextColor(Color4B(0,0,0,255));
//        label_price->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
//        label_price->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
//        label_price->setPosition(Vec2(name->getPositionX(),
//                                      name->getPositionY() - label_price->getContentSize().height));
//        addChild(label_price,3);
//        
//        auto price = Label::createWithSystemFont(price_.c_str(), "Arial", 28);
//        price->setDimensions(this->getContentSize().width / 4,
//                             this->getContentSize().height * 1 / 4);
//        price->setAnchorPoint(Vec2(0,0));
//        price->setTextColor(Color4B(242, 39, 0 ,255));
//        price->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
//        price->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
//        price->setPosition(Vec2(name->getPositionX() + price->getContentSize().width,
//                                name->getPositionY() - label_price->getContentSize().height));
//        addChild(price,3);

        

    }
    
    if (-1 == scene_info_)
    {
        
        auto id = Label::createWithSystemFont("订单编号： ", "Arial", 24);
        //        label->setContentSize(Size( size.width / 2, size.height / 10));
        id->setDimensions( size.width, size.height / 6);
        id->setTextColor(Color4B(0,0,0,255));
        id->setAnchorPoint(Vec2(0,0));
        id->setAlignment(cocos2d::TextHAlignment::LEFT);
        id->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        id->setPosition(Vec2(size.width / 12, (size.height / 6 - 2 ) / 6 * 2));
        
        cell->addChild(id);
        
        int strid = d1["order"][idx]["id"].GetInt();
        auto label_id = Label::createWithSystemFont(custom_string::int_to_string(strid).c_str(), "Arial", 24);
        //        label->setContentSize(Size( size.width / 2, size.height / 10));
        label_id->setDimensions( size.width, size.height / 6);
        label_id->setTextColor(Color4B(0,0,0,255));
        label_id->setAnchorPoint(Vec2(0,0));
        label_id->setAlignment(cocos2d::TextHAlignment::LEFT);
        label_id->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        label_id->setPosition(Vec2(size.width / 3, (size.height / 6 - 2 ) / 6 * 2));
        
        cell->addChild(label_id);
        
        auto price = Label::createWithSystemFont("订单金额： ", "Arial", 24);
        //        label->setContentSize(Size( size.width / 2, size.height / 10));
        price->setDimensions( size.width, size.height / 6);
        price->setTextColor(Color4B(0,0,0,255));
        price->setAnchorPoint(Vec2(0,0));
        price->setAlignment(cocos2d::TextHAlignment::LEFT);
        price->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        price->setPosition(Vec2(size.width / 12, (size.height / 6 - 2 ) / 6 ));
        
        cell->addChild(price);
        
        auto str = d1["order"][idx]["price"].GetString();
        auto label_price = Label::createWithSystemFont(str, "Arial", 24);
        //        label->setContentSize(Size( size.width / 2, size.height / 10));
        label_price->setDimensions( size.width, size.height / 6);
        label_price->setTextColor(Color4B(0,0,0,255));
        label_price->setAnchorPoint(Vec2(0,0));
        label_price->setAlignment(cocos2d::TextHAlignment::LEFT);
        label_price->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        label_price->setPosition(Vec2(size.width / 3, (size.height / 6 - 2 ) / 6 ));
        
        cell->addChild(label_price);
        
        
        auto label = Label::createWithSystemFont("交易状态： ", "Arial", 24);
        //        label->setContentSize(Size( size.width / 2, size.height / 10));
        label->setDimensions( size.width, size.height / 6);
        label->setTextColor(Color4B(0,0,0,255));
        label->setAnchorPoint(Vec2(0,0));
        label->setAlignment(cocos2d::TextHAlignment::LEFT);
        label->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        label->setPosition(Vec2(size.width / 12, 0));
        
        cell->addChild(label);
        
        std::string suc = d1["order"][idx]["confirm"].GetString();
        str = "未确定";
        if ("True" == suc)
            str = "派送中";
        suc = d1["order"][idx]["deal"].GetString();
        if ("True" == suc)
            str = "交易已完成";
        
        auto label_buff = Label::createWithSystemFont(str, "Arial", 24);
        //        label->setContentSize(Size( size.width / 2, size.height / 10));
        label_buff->setDimensions( size.width, size.height / 6);
        label_buff->setTextColor(Color4B(0,0,0,255));
        label_buff->setAnchorPoint(Vec2(0,0));
        label_buff->setAlignment(cocos2d::TextHAlignment::LEFT);
        label_buff->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        label_buff->setPosition(Vec2(size.width / 3, 0));
        
        cell->addChild(label_buff);
        
        auto address = Label::createWithSystemFont("送货地址： ", "Arial", 24);
        //        label->setContentSize(Size( size.width / 2, size.height / 10));
        address->setDimensions( size.width, size.height / 6);
        address->setTextColor(Color4B(0,0,0,255));
        address->setAnchorPoint(Vec2(0,0));
        address->setAlignment(cocos2d::TextHAlignment::LEFT);
        address->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        address->setPosition(Vec2(size.width / 12, -(size.height / 6 - 2 ) / 6 ));
        
        cell->addChild(address);
        
        
        str = d1["order"][idx]["address"].GetString();
        auto label_address = Label::createWithSystemFont(str, "Arial", 24);
        //        label->setContentSize(Size( size.width / 2, size.height / 10));
        label_address->setDimensions( size.width, size.height / 6);
        label_address->setTextColor(Color4B(0,0,0,255));
        label_address->setAnchorPoint(Vec2(0,0));
        label_address->setAlignment(cocos2d::TextHAlignment::LEFT);
        label_address->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        label_address->setPosition(Vec2(size.width / 3, -(size.height / 6 - 2 ) / 6 ));
        
        cell->addChild(label_address);
        
        auto time = Label::createWithSystemFont("交易时间： ", "Arial", 24);
        //        label->setContentSize(Size( size.width / 2, size.height / 10));
        time->setDimensions( size.width, size.height / 6);
        time->setTextColor(Color4B(0,0,0,255));
        time->setAnchorPoint(Vec2(0,0));
        time->setAlignment(cocos2d::TextHAlignment::LEFT);
        time->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        time->setPosition(Vec2(size.width / 12, -(size.height / 6 - 2 ) / 6 * 2));
        
        cell->addChild(time);
        
        str = d1["order"][idx]["time"].GetString();
        auto label_time = Label::createWithSystemFont(str, "Arial", 24);
        //        label->setContentSize(Size( size.width / 2, size.height / 10));
        label_time->setDimensions( size.width, size.height / 6);
        label_time->setTextColor(Color4B(0,0,0,255));
        label_time->setAnchorPoint(Vec2(0,0));
        label_time->setAlignment(cocos2d::TextHAlignment::LEFT);
        label_time->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        label_time->setPosition(Vec2(size.width / 3, -(size.height / 6 - 2 ) / 6 * 2));
        
        cell->addChild(label_time);
    }
    
    if (0 == scene_info_)
    {
    
    assert(d1.IsObject());
    const rapidjson::Value& user = d1["user"];
    
    assert(user.IsArray());

    
    std::string label_str;
//    if (table_num_ - 1 == idx)
//        idx = 99;
    
    log("cell's content size is %f",cell->getContentSize().height);
    

    
    auto label = Label::createWithSystemFont("", "Arial", 30);
    //        label->setContentSize(Size( size.width / 2, size.height / 10));
    label->setDimensions( size.width, size.height / 6);
    label->setTextColor(Color4B(0,0,0,255));
    label->setAnchorPoint(Vec2(0,0));
    label->setAlignment(cocos2d::TextHAlignment::LEFT);
    label->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    label->setPosition(Vec2(size.width / 8, 0 ));
    
    switch (idx) {
        case 0:
        {
            int i = 0;
            label_str = user[i].GetString();
            label_str = "用户名: " + label_str;
            label->setString(label_str.c_str());
            label->setPosition(Vec2(size.width / 8,
                                    (size.height / 6 - 2)  / 5));
            
            label_str = user[1].GetString();
            label_str = "学号 : " + label_str;
            auto id = Label::createWithSystemFont(label_str.c_str(), "Arial", 30);
            id->setDimensions( size.width, size.height / 6);
            id->setTextColor(Color4B(0,0,0,255));
            id->setAnchorPoint(Vec2(0,0));
            id->setAlignment(cocos2d::TextHAlignment::LEFT);
            id->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
            id->setPosition(Vec2(size.width / 8,
                                 0));

            cell->addChild(id);
            
            label_str = "True";
//            log("%s",user[2].GetString());
            if (label_str == user[2].GetString())
            {
                label_str = "管饭的";
            }
            else
            {
                label_str = "普通吃货";
            }
            
            label_str = "用户权限: " + label_str;
            auto root = Label::createWithSystemFont(label_str.c_str(), "Arial", 30);
            root->setDimensions( size.width, size.height / 6);
            root->setTextColor(Color4B(0,0,0,255));
            root->setAnchorPoint(Vec2(0,0));
            root->setAlignment(cocos2d::TextHAlignment::LEFT);
            root->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
            root->setPosition(Vec2(size.width / 8,
                                   -(size.height / 6 - 2) / 5));
            
            cell->addChild(root);
            
            
        }
            break;
            
        case 1:
            label->setString("订单信息");
            break;
            
        case 2:
            label->setString("退出登录");
            break;
            
        default:
            break;
    }
    cell->addChild(label);
    
    }
    
    return cell;
}

void ModCustomInfo::tableCellTouched(extension::TableView* table,
                             extension::TableViewCell* cell)
{
    //        CustomButton custombutton;
    //        auto *layer = (Layer *)this->getChildByTag(20);
    //        auto ttf = (LabelTTF *)layer->getChildByTag(22);
    //        ttf->setString(custombutton.IntToString(cell->getIdx()));
    if (0 == scene_info_)
    {
        if (0 == cell->getIdx())
        {
        }
        
        else if (1 == cell->getIdx())
        {
            //        GetClientorder();
            Director::getInstance()->replaceScene(ModCustomInfo::createScene(-1));
        }
        
        else
        {
            LogInfo::SetLogOut();
            UserLogOut();
            //        Director::getInstance()->popScene();
            auto* scene = ModCustom::createScene();
            Director::getInstance()->replaceScene(scene);
        }
    }
    
    if (-1 == scene_info_)
    {
        rapidjson::Document d;
        d.Parse<0>(get_into_.c_str());
        auto id = d["order"][cell->getIdx()]["id"].GetInt();
        log("id is %d",id);
        auto* scene = ModCustomInfo::createScene(id);
        Director::getInstance()->replaceScene(scene);

    }
    
    CCLOG("%zi", cell->getIdx());
    //        log("touch is %ld",cell->getIdx());
}//CustomTableview::tableCellTouched

void ModCustomInfo::scrollViewDidScroll(cocos2d::extension::ScrollView *view)
{
    //        auto *layer = (Layer *)this->getChildByTag(20);
    //        auto *p_slider = (Slider *)layer->getChildByTag(21);
    //        auto point = view->getContentOffset();
    //        Point pos = view->getContentSize() - view->getViewSize();
    //        float percent = 100 + (point.y / pos.y) * 100;
    //        std::cout<<"viewsize:  "<<pos.y<<std::endl;
    //        std::cout<<"ContentOffset:  "<<view->getContentOffset().y<<std::endl;
    //        p_slider->setPercent(percent);
}//CustomTableview::scrollViewDidScroll

void ModCustomInfo::GetClientorder()
{
    
    auto path = FileUtils::getInstance()->getWritablePath() + "userinfo.json";
    
    auto user = FileUtils::getInstance()->getStringFromFile(path.c_str());
    
    HttpRequest *request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::POST);
    request->setTag("POST test");
    
//    rapidjson::Document d1;
//    rapidjson::Document::AllocatorType& allocator1 = d1.GetAllocator();
//    d1.Parse<0>(user.c_str());
//    
//    
//    d1.AddMember("order", "3", allocator1);
    
    
//    rapidjson::StringBuffer buffer;
//    rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
//    d1.Accept(write);
    
    rapidjson::Document d;
    auto jsonpath = FileUtils::getInstance()->getWritablePath() + "config.json";
    auto jsonstr = FileUtils::getInstance()->getStringFromFile(jsonpath.c_str());
    d.Parse<0>(jsonstr.c_str());
    assert(d.IsObject());
    std::string ip = d["ip"].GetString();
    std::string port = d["port"].GetString();
    
    auto str = "http://" + ip + ":" + port + "/clientorder/";
//    log("%s",buffer.GetString());
    
    request->setUrl(str.c_str());
    //    std::string str = "username=123&password=123";
    if (-1 == scene_info_)
    {
        request->setRequestData(user.c_str(), user.size());
    }
    else
    {
//        request->setRequestData(buffer.GetString(), buffer.Size());
        request->setRequestData(user.c_str(), user.size());
    }
    request->setResponseCallback(CC_CALLBACK_2(ModCustomInfo::ClientorderCallback, this));
    
    HttpClient::getInstance()->send(request);
    request->release();
}

void ModCustomInfo::ClientorderCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
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
    
    if (500 == statusCode && 0 == ConfigJson::GetBoomNum() && 32 > reget_)
    {
        reget_++;
        GetClientorder();
        return;
    }
    
    if (response->isSucceed())
    {
        get_into_ = "";
        
        std::vector<char>* v = response->getResponseData();
        for (int i = 0; i < v->size(); i++)
        {
            //            printf("%c", v->at(i));
            get_into_ = get_into_ + v->at(i);
        }
        log("%s",get_into_.c_str());
        printf("\n");
        
        rapidjson::Document d1;
        d1.Parse<0>(get_into_.c_str());
        
        if (d1.HasParseError())
        {
            log("%s",d1.GetParseError());
            return;
        }
        
        assert(d1.IsObject());
        std::string test = "succeed";
        log ("%s",d1["response"].GetString());
        
        
        CreateTableView();
        
    }

}

void ModCustomInfo::GetClientInfo()
{
    auto path = FileUtils::getInstance()->getWritablePath() + "userinfo.json";
    
    auto user = FileUtils::getInstance()->getStringFromFile(path.c_str());
    
    HttpRequest *request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::POST);
    request->setTag("POST test");
    
    rapidjson::Document d1;
    rapidjson::Document::AllocatorType& allocator1 = d1.GetAllocator();
    d1.Parse<0>(user.c_str());
    
    
//    d1.AddMember("order", custom_string::int_to_string(scene_info_).c_str(), allocator1);
//    d1.AddMember("order", scene_info_, allocator1);
    d1.AddMember("order", scene_info_, allocator1);
    
    
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
    
    auto str = "http://" + ip + ":" + port + "/clientorder/";
    log("%s",buffer.GetString());
    
    request->setUrl(str.c_str());
    //    std::string str = "username=123&password=123";
    if (-1 == scene_info_)
    {
        request->setRequestData(user.c_str(), user.size());
    }
    else
    {
        request->setRequestData(buffer.GetString(), buffer.Size());
    }
    request->setResponseCallback(CC_CALLBACK_2(ModCustomInfo::ClientInfoCallback, this));
    
    HttpClient::getInstance()->send(request);
    request->release();
}

void ModCustomInfo::ClientInfoCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
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
    if (500 == statusCode && 0 == ConfigJson::GetBoomNum() && 32 > reget_)
    {
        reget_++;
            GetClientInfo();
            return;
        }
//    
//    if (500 == statusCode && 0 == ConfigJson::GetBoomNum())
//    {
//        GetClientInfo();
//    }
    
    if (response->isSucceed())
    {
        get_into_ = "";
        
        std::vector<char>* v = response->getResponseData();
        for (int i = 0; i < v->size(); i++)
        {
            //            printf("%c", v->at(i));
            get_into_ = get_into_ + v->at(i);
        }
        log("%s",get_into_.c_str());
        printf("\n");
        
        rapidjson::Document d1;
        d1.Parse<0>(get_into_.c_str());
        
        if (d1.HasParseError())
        {
            log("%s",d1.GetParseError());
            return;
        }
        
        assert(d1.IsObject());
        std::string test = "succeed";
        log ("%s",d1["response"].GetString());
        
        CreateFoodOrder();
        CreateTableView();
        
        
    }
}





