//
//  mod_food_show.cpp
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/28/15.
//
//

#include "mod_food_show.h"

#include "mod_main_menu.h"
ModFoodShow::ModFoodShow(std::string str):
food_id_(-1),
is_network_done_(-1)
{
    str_ = str;
    rapidjson::Document d1;
    d1.Parse<0>(str.c_str());
    food_id_ = d1["id"].GetInt();
    canteen_ = d1["canteen"].GetString();
    name_ = d1["name"].GetString();
    img_ad_ = d1["img"].GetString();
    description_ = d1["description"].GetString();
    price_ = d1["price"].GetString();
}

ModFoodShow::~ModFoodShow()
{
    
}

bool ModFoodShow::init()
{
    DownloadPicture();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto size = Director::getInstance()->getVisibleSize();
    
    this->setContentSize(Size(size.width, size.height / 5));
    
    auto* back_layer = LayerColor::create(Color4B(244, 245, 255, 255));
    back_layer->setContentSize(this->getContentSize());

//    back_layer->setPosition(Vec2(origin.x, this->getPositionY()));
    addChild(back_layer,1);
//    InitFoodShow();
    this->scheduleUpdate();
    return true;
}

ModFoodShow* ModFoodShow::Create(std::string info)
{
    auto* ret = new ModFoodShow(info);
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
    if (0 == is_network_done_)
    {
        this->unscheduleUpdate();
        InitFoodShow();
    }
}

int ModFoodShow::InitFoodShow()
{
    log("init food show");
    
    auto scale = this->getContentSize().width / (200 * 4);
    
    auto path = FileUtils::getInstance()->getWritablePath() + "food_" + custom_string::int_to_string(food_id_) + ".png";
    img_name_ = path;
    img_ = Sprite::create(path);
    img_->setScale(this->getContentSize().height * 0.9 / img_->getContentSize().height );
    img_->setAnchorPoint(Vec2(0,0));
    img_->setPosition(Vec2(this->getContentSize().height * 0.05,
                           this->getContentSize().height * 0.05));
    addChild(img_,3);
    
    auto name = Label::createWithSystemFont(name_.c_str(), "Arial", 24);
    name->setDimensions(this->getContentSize().width / 4,
                              this->getContentSize().height * 1 / 4);
    name->setAnchorPoint(Vec2(0,0));
    name->setTextColor(Color4B(0,0,0,255));
    name->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    name->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    name->setPosition(Vec2(this->getContentSize().width / 3,
                           this->getContentSize().height * 3 / 4));
    addChild(name,3);
    
    auto label_price = Label::createWithSystemFont("单价：", "Arial", 24);
    label_price->setDimensions(this->getContentSize().width / 4,
                              this->getContentSize().height * 1 / 4);
    label_price->setAnchorPoint(Vec2(0,0));
    label_price->setTextColor(Color4B(0,0,0,255));
    label_price->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    label_price->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    label_price->setPosition(Vec2(name->getPositionX(),
                                  name->getPositionY() - label_price->getContentSize().height));
    addChild(label_price,3);
    
    auto price = Label::createWithSystemFont(price_.c_str(), "Arial", 28);
    price->setDimensions(this->getContentSize().width / 4,
                               this->getContentSize().height * 1 / 4);
    price->setAnchorPoint(Vec2(0,0));
    price->setTextColor(Color4B(242, 39, 0 ,255));
    price->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    price->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    price->setPosition(Vec2(name->getPositionX() + price->getContentSize().width,
                                  name->getPositionY() - label_price->getContentSize().height));
    addChild(price,3);
    
    auto button_shop = Button::create("shop_button.png");
    button_shop->setScale(this->getContentSize().width / (button_shop->getContentSize().width * 4));
    button_shop->setAnchorPoint(Vec2(0,0));
    button_shop->setPosition(Vec2(this->getContentSize().width * 2 / 5,
                                  this->getContentSize().height * 1 / 5));
    button_shop->addTouchEventListener(CC_CALLBACK_2(ModFoodShow::ButtonShopCallback, this));
    addChild(button_shop,3);
    
    
    
    auto button_info = Button::create("info_button.png");
    button_info->setScale(this->getContentSize().width / (button_info->getContentSize().width * 4));
    button_info->setAnchorPoint(Vec2(0,0));
    button_info->setPosition(Vec2(button_shop->getPositionX() + button_shop->getContentSize().width * 1.1 * scale,
                                  button_shop->getPositionY()));
    button_info->addTouchEventListener(CC_CALLBACK_2(ModFoodShow::ButtonInfoCallback, this));
    addChild(button_info,3);
    
    
    
    log("food show over");
    
    
    return 0;
}

void ModFoodShow::ButtonInfoCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->pushScene(ModFoodInfo::CreateScene(str_));
            break;
            
        default:
            break;
    }
}

void ModFoodShow::ButtonShopCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
//            GetList();
            if (0 == LogInfo::GetLogIn())
                BuySomething();
            else
                Director::getInstance()->replaceScene(ModMainMenu::createScene(0));
            break;
            
        default:
            break;
    }
}

void ModFoodShow::LogInCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
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
        log("%s",d1["food"][1]["name"].GetString());
        log("%d",d1["food"].Size());
        assert(d1.IsObject());
        std::string test = "food";
        log ("%s",d1["response"].GetString());
        if (test == d1["response"].GetString())
        {
//            auto scene = ModCustomInfo::createScene();
//            Director::getInstance()->replaceScene(scene);
        }
        

    }
    
    //    sprintf(test, response->getResponseDataString());
    
    
}

//std::wstring ModFoodShow::UTF8ToWString(const char* lpcszString)
//{
//    int len = strlen(lpcszString);
//    int unicodeLen = ::MultiByteToWideChar(CP_UTF8, 0, lpcszString, -1, NULL, 0);
//    wchar_t* pUnicode;
//    pUnicode = new wchar_t[unicodeLen + 1];
//    memset((void*)pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
//    ::MultiByteToWideChar(CP_UTF8, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
//    wstring wstrReturn(pUnicode);
//    delete [] pUnicode;
//    return wstrReturn;
//}

void ModFoodShow::GetList()
{
    log("POST");
    HttpRequest *request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::GET);
    //    request->setRequestType(HttpRequest::Type::GET);
    request->setTag("POST test");
    //    request->setUrl("http://d.hiphotos.baidu.com/image/pic/item/d50735fae6cd7b8985adc8980d2442a7d8330ee3.jpg");
    
    rapidjson::Document d;
    auto jsonpath = FileUtils::getInstance()->getWritablePath() + "config.json";
    auto jsonstr = FileUtils::getInstance()->getStringFromFile(jsonpath.c_str());
    d.Parse<0>(jsonstr.c_str());
    assert(d.IsObject());
    std::string ip = d["ip"].GetString();
    std::string port = d["port"].GetString();
    
    auto str = "http://" + ip + ":" + port + "/clientfood/?choose=0";
    request->setUrl(str.c_str());
    
    
    
    
    request->setResponseCallback(CC_CALLBACK_2(ModFoodShow::LogInCallback, this));
    //    HttpClient::getInstance()->sendImmediate(request);
    HttpClient::getInstance()->send(request);
    request->release();
}

int ModFoodShow::DownloadPicture()
{
    HttpRequest *request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::GET);
    request->setTag("downLoad tag 1");
    //    request->setUrl("http://d.hiphotos.baidu.com/image/pic/item/d50735fae6cd7b8985adc8980d2442a7d8330ee3.jpg");
    
    request->setUrl(img_ad_.c_str());
    
    request->setResponseCallback(CC_CALLBACK_2(ModFoodShow::OnDownloadComplete, this));
    HttpClient::getInstance()->sendImmediate(request);
    request->release();
    return 0;
}

void ModFoodShow::OnDownloadComplete(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
    if (!response) {
        return;
    }
    
    if (!response->isSucceed()) {
        CCLOG("error %s", response->getErrorBuffer());
        return;
    }
    
    
    if (response->isSucceed())
    {
        std::vector<char> *buffData = response->getResponseData();
        char *buff = (char *)malloc(buffData->size());
        std::copy(buffData->begin(), buffData->end(), buff);
        //        auto fileName = FileUtils::getInstance()->getWritablePath() +"food_" + std::to_string(food_id_) + ".png";


        
        auto fileName = FileUtils::getInstance()->getWritablePath();
        fileName += "food_";
        fileName += custom_string::int_to_string(food_id_);
        fileName += ".png";
        FILE *fp = fopen(fileName.c_str(), "wb+");
        fwrite(buff, 1, buffData->size(), fp);
        fclose(fp);
        
        is_network_done_ = 0;
    }
}

void ModFoodShow::BuySomething()
{
    auto path = FileUtils::getInstance()->getWritablePath() + "userinfo.json";
    
    auto user = FileUtils::getInstance()->getStringFromFile(path.c_str());
    
    HttpRequest *request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::POST);
    request->setTag("POST test");
    
    rapidjson::Document d1;
    rapidjson::Document::AllocatorType& allocator1 = d1.GetAllocator();
    d1.Parse<0>(user.c_str());
    
    
    d1.AddMember("food", custom_string::int_to_string(food_id_).c_str(), allocator1);
    
    
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
    
    request->setResponseCallback(CC_CALLBACK_2(ModFoodShow::BuyCallback, this));
    
    HttpClient::getInstance()->send(request);
    request->release();
}

void ModFoodShow::BuyCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
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
    
    if (500 == statusCode && 0 == ConfigJson::GetBoomNum())
    {
        BuySomething();
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

//template <typename T>
//std::string to_string_template(const T& t) {
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    std::ostringstream os;
//    os << t;
//    return os.str();
//#else
//    
//    return std::to_string(t);
//    
//#endif
//}



//
//  custom_string.h
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 4/24/15.
//
//

