//
//  mod_custom_info.cpp
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/15/15.
//
//

#include "mod_custom_info.h"
#include "mod_custom.h"

bool ModCustomInfo::init()
{
    auto layer_background = LayerColor::create(Color4B(240,240,255,255));
    addChild(layer_background);
    InitTop();
    GetInfo();
    return true;
}

Scene* ModCustomInfo::createScene()
{
    auto scene = Scene::create();
    auto layer = ModCustomInfo::create();
    scene->addChild(layer);
    return scene;
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
    
    auto button_shop = Button::create("shop.png");
    button_shop->setScale(scale);
    button_shop->setPosition(Vec2(layer_top_->getPositionX() + size.width - button_back->getContentSize().width / 2 * scale,layer_top_->getPositionY() + layer_top_->getContentSize().height / 2));
    button_shop->addTouchEventListener(CC_CALLBACK_2(ModCustomInfo::ButtonShopCallback, this));
    
    
    addChild(button_back,2);
    addChild(button_shop,2);
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
    GetInfo();
    
    
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
    if (500 == statusCode)
    {
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
    
    auto str = "http://" + ConfigJson::GetConfigIp() + ":" + ConfigJson::GetConfigPort() + "/clientlogout/";
    
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
    if (500 == statusCode)
    {
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
        
        CreateTableView();
    }
    
    
    
}
void ModCustomInfo::GetInfo()
{
    log("GET");
    HttpRequest *request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::GET);
    request->setTag("POST test");
    
    auto str = "http://" + ConfigJson::GetConfigIp() + ":" + ConfigJson::GetConfigPort() + "/clientuserinfo/";
    
    request->setUrl(str.c_str());
    //    std::string str = "username=123&password=123";
    //    request->setRequestData(str.c_str(), str.size());
    
    
    
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


void ModCustomInfo::CreateTableView()
{
    auto size = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    menu_ = extension::TableView::create(this, Size(Size(size.width, size.height - layer_top_->getContentSize().height)));
    menu_->setPosition(Vec2(origin.x, origin.y));
    //        menu_->setPosition(Vec2(origin.x + size.width / 4, origin.y));
    
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
    
    rapidjson::Value& user = d1["user"];
    
    
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
    table_num_ = user.Size() - 2;
    return table_num_;
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
    
    assert(d1.IsObject());
    const rapidjson::Value& user = d1["user"];
    
    assert(user.IsArray());
    

    
    

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
    
    std::string label_str;
    if (table_num_ - 1 == idx)
        idx = 99;
    
    switch (idx) {
        case 0:
            label_str = user[1].GetString();

            break;
            
        case 99:
            label_str = "退出登录";
            break;
            
        default:
            break;
    }
    

    
    auto label = Label::createWithSystemFont(label_str.c_str(), "Arial", 30);
    //        label->setContentSize(Size( size.width / 2, size.height / 10));
    label->setDimensions( size.width, size.height / 6);
    label->setTextColor(Color4B(0,0,0,255));
    label->setAnchorPoint(Vec2(0,0));
    label->setPosition(Vec2(size.width / 8, 0 ));
//    label->setAnchorPoint(0,0);
    //        label->setPosition(bg_sprite->getContentSize().width / 2, bg_sprite->getContentSize().height / 2);
    label->setAlignment(cocos2d::TextHAlignment::LEFT);
    label->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    cell->addChild(label);
    

    
    return cell;
}

void ModCustomInfo::tableCellTouched(extension::TableView* table,
                             extension::TableViewCell* cell)
{
    //        CustomButton custombutton;
    //        auto *layer = (Layer *)this->getChildByTag(20);
    //        auto ttf = (LabelTTF *)layer->getChildByTag(22);
    //        ttf->setString(custombutton.IntToString(cell->getIdx()));
    if (0 == cell->getIdx())
    {
    }
    else
    {
        LogInfo::SetLogOut();
        UserLogOut();
        //        Director::getInstance()->popScene();
        auto* scene = ModCustom::createScene();
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

