//
//  mod_main_menu.cpp
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/15/15.
//
//

#include "mod_main_menu.h"
#include "mod_custom.h"

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
    
//    http_->UserLogIn();
    
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
    edit_name_ = EditBox::create(Size(size.width * 0.5,size.height * 0.1 ), "bt.png");
    edit_name_->setPosition(Vec2(origin.x + size.width / 2,origin.y + size.height * 3 / 5));
    edit_name_->setMaxLength(16);
    edit_name_->setFontColor(Color3B(0,0,0));
//    edit_name_->setFontSize(24);
    edit_name_->setDelegate(this);
    addChild(edit_name_,1);
    
    edit_pass_ = EditBox::create(Size(size.width * 0.5,size.height * 0.1 ), "bt.png");
    edit_pass_->setPosition(Vec2(origin.x + size.width / 2,origin.y + edit_name_->getPositionY() - edit_pass_->getContentSize().height * 1.5 ));
    edit_pass_->setMaxLength(16);
    edit_pass_->setFontColor(Color3B(0,0,0));
//    edit_pass_->setFontSize(24);
    edit_pass_->setDelegate(this);
    addChild(edit_pass_,1);
    
    if (233 != login_)
    {
        if (0 == login_);
            edit_pass_->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);
        auto label_name = Label::createWithSystemFont("用户名:", "Airal", 24);
        label_name->setDimensions(edit_name_->getContentSize().width ,edit_name_->getContentSize().height  );
        label_name->setAnchorPoint(Vec2(0.5, 0.5));
        label_name->setAlignment(cocos2d::TextHAlignment::CENTER);
        label_name->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        label_name->setPosition(Vec2(origin.x + (edit_name_->getPositionX() - label_name->getContentSize().width / 2) / 2,
                                     origin.y + edit_name_->getPositionY()));
        label_name->enableShadow();
        label_name->setTextColor(Color4B(240,240,255,255));
        addChild(label_name,1);
        
        auto label_pass = Label::createWithSystemFont("密码:", "Airal", 24);
        label_pass->setDimensions(edit_name_->getContentSize().width,edit_name_->getContentSize().height );
        label_pass->setAnchorPoint(Vec2(0.5, 0.5));
        label_pass->setAlignment(cocos2d::TextHAlignment::CENTER);
        label_pass->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        label_pass->setPosition(Vec2(origin.x + (edit_pass_->getPositionX() - edit_pass_->getContentSize().width / 2) / 2,
                                     origin.y + edit_pass_->getPositionY()));
        label_pass->enableShadow();
        label_pass->setTextColor(Color4B(240,240,255,255));
        addChild(label_pass,1);
    }
    else
    {
        
//        user_name_ =ConfigJson::GetConfigIp();
//        edit_name_->setPlaceHolder(user_name_.c_str());
//        edit_name_->setPlaceholderFontColor(Color3B(0,0,0));
//        edit_name_->setPlaceholderFontSize(10);
//        edit_name_->setFontSize(24);
        rapidjson::Document d;
        auto jsonpath = FileUtils::getInstance()->getWritablePath() + "config.json";
        auto jsonstr = FileUtils::getInstance()->getStringFromFile(jsonpath.c_str());
        d.Parse<0>(jsonstr.c_str());
        assert(d.IsObject());
        user_name_ = d["ip"].GetString();
        std::string port = d["port"].GetString();
        
        edit_pass_->setPlaceholderFontSize(10);
        edit_pass_->setPlaceholderFontColor(Color3B(0,0,0));
        edit_pass_->setPlaceHolder(port.c_str());
        edit_name_->setInputMode(cocos2d::ui::EditBox::InputMode::DECIMAL);
        edit_pass_->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);

        auto label_name = Label::createWithSystemFont("地址:", "Airal", 24);
        label_name->setDimensions(edit_name_->getContentSize().width ,edit_name_->getContentSize().height  );
        label_name->setAnchorPoint(Vec2(0.5, 0.5));
        label_name->setAlignment(cocos2d::TextHAlignment::CENTER);
        label_name->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        label_name->setPosition(Vec2(origin.x + (edit_name_->getPositionX() - label_name->getContentSize().width / 2) / 2,
                                     origin.y + edit_name_->getPositionY()));
        label_name->enableShadow();
        label_name->setTextColor(Color4B(240,240,255,255));
        addChild(label_name,1);
        
        auto label_pass = Label::createWithSystemFont("端口:", "Airal", 24);
        label_pass->setDimensions(edit_name_->getContentSize().width,edit_name_->getContentSize().height );
        label_pass->setAnchorPoint(Vec2(0.5, 0.5));
        label_pass->setAlignment(cocos2d::TextHAlignment::CENTER);
        label_pass->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        label_pass->setPosition(Vec2(origin.x + (edit_pass_->getPositionX() - edit_pass_->getContentSize().width / 2) / 2,
                                     origin.y + edit_pass_->getPositionY()));
        label_pass->enableShadow();
        label_pass->setTextColor(Color4B(240,240,255,255));
        addChild(label_pass,1);

    }
    

    if (login_ == -1)
    {
        
        edit_id_ = EditBox::create(Size(size.width * 0.5,size.height * 0.1 ), "bt.png");
        edit_id_->setPosition(Vec2(origin.x + size.width / 2,origin.y + edit_name_->getPositionY() + edit_pass_->getContentSize().height * 1.5 ));
        edit_id_->setMaxLength(10);
        edit_id_->setFontColor(Color3B(0,0,0));
        //    edit_name_->setFontSize(24);
        edit_id_->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
        edit_id_->setDelegate(this);
        addChild(edit_id_,1);
        
        auto label_id = Label::createWithSystemFont("学号:", "Airal", 24);
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
    if (editBox == edit_id_)
    {
        user_id_ = text;
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
    auto scale = Director::getInstance()->getVisibleSize().width / (signup->getContentSize().width * 4);
    
    if (login_ == 0)
    {
    auto login = Button::create("login.png");
    auto logout = Button::create("close.png");
    //登陆
    login->setScale(scale);
    login->setAnchorPoint(Vec2(0.5,0.5));
    login->setPosition(Vec2(origin.x + size.width  /3,
                            origin.y + edit_pass_->getPositionY() - edit_pass_->getContentSize().height * 1.5));
    login->addTouchEventListener(CC_CALLBACK_2(ModMainMenu::ButtonLoginCallback, this));
    addChild(login,1);
    
    //注册
    signup->setScale(scale);
    signup->setAnchorPoint(Vec2(0.5,0.5));
    signup->setPosition(Vec2(origin.x + size.width *2 / 3,
                             origin.y + edit_pass_->getPositionY() - edit_pass_->getContentSize().height * 1.5));
    signup->addTouchEventListener(CC_CALLBACK_2(ModMainMenu::ButtonSignupCallback, this));
    addChild(signup,1);
    
    //离开
    logout->setPosition(Vec2(origin.x + Director::getInstance()->getVisibleSize().width - logout->getContentSize().width,origin.y + logout->getContentSize().height));
    logout->addTouchEventListener(CC_CALLBACK_2(ModMainMenu::ButtonLogoutCallback, this));
    addChild(logout,1);
    }
    
    else if(233 == login_)
    {
        auto submit = Button::create("changed.png");
        submit->setScale(scale);
        submit->setAnchorPoint(Vec2(0.5,0.5));
        submit->setPosition(Vec2(origin.x + size.width  /3,
                                 origin.y + edit_pass_->getPositionY() - edit_pass_->getContentSize().height * 1.5));
        submit->addTouchEventListener(CC_CALLBACK_2(ModMainMenu::ButtonUpdateCallback, this));
        addChild(submit,1);
        
        //离开
        auto logout = Button::create("close.png");
        logout->setPosition(Vec2(origin.x + Director::getInstance()->getVisibleSize().width - logout->getContentSize().width,origin.y + logout->getContentSize().height));
        logout->addTouchEventListener(CC_CALLBACK_2(ModMainMenu::ButtonLogoutCallback, this));
        addChild(logout,1);
    }
    
    else
    {
        auto cancel = Button::create("cancel.png");
        
        
        signup->setScale(scale);
        signup->setAnchorPoint(Vec2(0.5,0.5));
        signup->setPosition(Vec2(origin.x + size.width  /3,
                                 origin.y + edit_pass_->getPositionY() - edit_pass_->getContentSize().height * 1.5));
        signup->addTouchEventListener(CC_CALLBACK_2(ModMainMenu::ButtonCancelCallback, this));
        addChild(signup,1);
        
        
        cancel->setScale(scale);
        cancel->setAnchorPoint(Vec2(0.5,0.5));
        cancel->setPosition(Vec2(origin.x + size.width *2 / 3,
                                 origin.y + edit_pass_->getPositionY() - edit_pass_->getContentSize().height * 1.5));
        cancel->addTouchEventListener(CC_CALLBACK_2(ModMainMenu::ButtonLogoutCallback, this));
        addChild(cancel,1);
        
    }
    
}

void ModMainMenu::ButtonUpdateCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
        {
            rapidjson::Document d;
            auto path = FileUtils::getInstance()->getWritablePath() + "config.json";
            auto str = FileUtils::getInstance()->getStringFromFile(path.c_str());
            d.Parse<0>(str.c_str());
            d["ip"].SetString(user_name_.c_str());
            d["port"].SetString(user_password_.c_str());
            
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
            d.Accept(write);
            FILE* file = fopen(path.c_str(), "wb");
            if (file)
            {
                fputs(buffer.GetString(), file);
                fclose(file);
            }
            
        }
            break;
        default:
            break;
    }
}

void ModMainMenu::ButtonLoginCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
        {
            UserLogIn();
//            log("login");
//            auto* scene = ModCustom::createScene();
//            auto etc = TransitionMoveInR::create(0.5, scene);
//            Director::getInstance()->pushScene(etc);
        }
            break;
        default:
            break;
    }
}

void ModMainMenu::ButtonCancelCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
//    Director::getInstance()->popScene();
    switch (type)
    {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
        {
            UserSignUp();
        }
            break;
        default:
            break;
    }
}



void ModMainMenu::ButtonSignupCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
        {
            
                Director::getInstance()->replaceScene(createScene(-1));
        }
            break;
        default:
            break;
    }
}


void ModMainMenu::ButtonLogoutCallback(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
        {
            
            Director::getInstance()->replaceScene(ModCustom::createScene());
        }
            break;
        default:
            break;
    }
//    http_->UserTest();
//    Director::getInstance()->popScene();
    
    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//    return;
//#endif
//    
//    Director::getInstance()->end();
//    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
}


#pragma mark - Network

void ModMainMenu::LogInCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
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
    if (500 == statusCode && 0 == ConfigJson::GetBoomNum() && 100 > reget_)
    {
        reget_++;
        //        GetClientorder();
        UserLogIn();
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
        
        
        if (500 == statusCode && 0 == ConfigJson::GetBoomNum() && 100 > reget_)
        {
            reget_++;
            UserLogIn();
            return;
        }
        
        assert(d1.IsObject());
        std::string test = "succeed";
        log ("%s",d1["response"].GetString());
        if (test == d1["response"].GetString())
        {
            LogInfo::SetLogIn();
            auto scene = ModCustomInfo::createScene(0);
            Director::getInstance()->replaceScene(scene);
        }
        
        
    }
    
    
    
}

void ModMainMenu::UserLogIn()
{
    log("POST");
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
    
        auto str = "http://" + ip + ":" + port + "/clientlogin/";
    request->setUrl(str.c_str());
    
    
//    std::string str = "{\"username\":\"" + user_name_ + "\",\"password\":\"" + user_password_ + "\"}";
    
    rapidjson::Document d1;
    rapidjson::Document::AllocatorType& allocator = d1.GetAllocator();
    d1.SetObject();
    
    d1.AddMember("username", user_name_.c_str(), allocator);
    d1.AddMember("password", user_password_.c_str(), allocator);
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
    d1.Accept(write);
    log("%s",buffer.GetString());   
    
    request->setRequestData(buffer.GetString(), buffer.Size());
    
    request->setResponseCallback(CC_CALLBACK_2(ModMainMenu::LogInCallback, this));
    //    HttpClient::getInstance()->sendImmediate(request);
    HttpClient::getInstance()->send(request);
    request->release();
    
    
    auto path = FileUtils::getInstance()->getWritablePath() + "userinfo.json";
    log("new str is %s",buffer.GetString());
    FILE* file = fopen(path.c_str(), "wb");
    if(file)
    {
        fputs(buffer.GetString(), file);
        fclose(file);
    }

}

void ModMainMenu::SignUpCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
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
    if (500 == statusCode && 0 == ConfigJson::GetBoomNum() && 100 > reget_)
    {
        reget_++;
        //        GetClientorder();
//        UserLogIn();
        UserSignUp();
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
        if (test == d1["response"].GetString())
        {
            LogInfo::SetLogIn();
            auto scene = ModCustomInfo::createScene(0);
            Director::getInstance()->replaceScene(scene);
        }
        
        
    }
    
}

void ModMainMenu::UserSignUp()
{
    
    log("POST");
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
    
    auto str = "http://" + ip + ":" + port + "/clientregist/";
    request->setUrl(str.c_str());
    
    
    //    std::string str = "{\"username\":\"" + user_name_ + "\",\"password\":\"" + user_password_ + "\"}";
    
    rapidjson::Document d1;
    rapidjson::Document::AllocatorType& allocator = d1.GetAllocator();
    d1.SetObject();
    
    d1.AddMember("username", user_name_.c_str(), allocator);
    d1.AddMember("password", user_password_.c_str(), allocator);
    d1.AddMember("email", user_id_.c_str(), allocator);
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
    d1.Accept(write);
    log("%s",buffer.GetString());
    
    request->setRequestData(buffer.GetString(), buffer.Size());
    
    request->setResponseCallback(CC_CALLBACK_2(ModMainMenu::SignUpCallback, this));
    
    HttpClient::getInstance()->send(request);
    request->release();
    
    
    auto path = FileUtils::getInstance()->getWritablePath() + "userinfo.json";
    log("new str is %s",buffer.GetString());
    FILE* file = fopen(path.c_str(), "wb");
    if(file)
    {
        fputs(buffer.GetString(), file);
        fclose(file);
    }
    
    
}

