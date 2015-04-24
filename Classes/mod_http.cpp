//
//  mod_http.cpp
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/28/15.
//
//

#include "mod_http.h"

ModHttp::ModHttp()
{
    
}

ModHttp::~ModHttp()
{
    
}

ModHttp* ModHttp::Create()
{
    auto* ret = new ModHttp;
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

bool ModHttp::init()
{
    return true;
    
}

int ModHttp::get_socks_(-1);
int ModHttp::go_int_(-1);

int ModHttp::DownloadPicture(int img_id)
{
    HttpRequest *request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::GET);
    request->setTag("downLoad tag 1");
//    request->setUrl("http://d.hiphotos.baidu.com/image/pic/item/d50735fae6cd7b8985adc8980d2442a7d8330ee3.jpg");
    
        request->setUrl("http://image.baidu.com/i?tn=download&word=download&ie=utf8&fr=detail&url=http%3A%2F%2Frecipe0.hoto.cn%2Fpic%2Frecipe%2Fg_175%2Fa8%2Fe5%2F255400_d5f8d3.jpg&thumburl=http%3A%2F%2Fimg4.imgtn.bdimg.com%2Fit%2Fu%3D3177816433%2C3200266843%26fm%3D21%26gp%3D0.jpg");
    
    request->setResponseCallback(CC_CALLBACK_2(ModHttp::OnDownloadComplete, this));
    HttpClient::getInstance()->sendImmediate(request);
    request->release();
    SetGetSocksing();
    return 0;
}



void ModHttp::OnDownloadComplete(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
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
        auto fileName = FileUtils::getInstance()->getWritablePath() +"ceshi.jpg";
        FILE *fp = fopen(fileName.c_str(), "wb+");
        fwrite(buff, 1, buffData->size(), fp);
        fclose(fp);
        SetGoIntDone();
        SetGetSocksDone();
    }
}

void ModHttp::LogInCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
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
        
        std::vector<char>* v = response->getResponseData();
        for (int i = 0; i < v->size(); i++)
        {
            printf("%c", v->at(i));
        }
        printf("\n");
    }
//    char test[64] = {};
    
//    sprintf(test, response->getResponseDataString());
    
    
}

void ModHttp::UserLogIn()
{
    log("POST");
    HttpRequest *request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::POST);
//    request->setRequestType(HttpRequest::Type::GET);
    request->setTag("POST test");
    //    request->setUrl("http://d.hiphotos.baidu.com/image/pic/item/d50735fae6cd7b8985adc8980d2442a7d8330ee3.jpg");
    
    request->setUrl("http://192.168.2.152:8000/clientlogin/");
    std::string str = "username=123&password=123";
    request->setRequestData(str.c_str(), str.size());


    
    
    request->setResponseCallback(CC_CALLBACK_2(ModHttp::LogInCallback, this));
//    HttpClient::getInstance()->sendImmediate(request);
    HttpClient::getInstance()->send(request);
    request->release();
}


void ModHttp::UserLogOut()
{
    log("GET");
    HttpRequest *request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::GET);
    request->setTag("POST test");
    
    request->setUrl("http://192.168.2.152:8000/clientlogin/");
    std::string str = "username=123&password=123";
    //    request->setRequestData(str.c_str(), str.size());
    
    
    
    request->setResponseCallback(CC_CALLBACK_2(ModHttp::LogInCallback, this));
    HttpClient::getInstance()->send(request);
    request->release();
}


void ModHttp::UserTest()
{
    log("Test 8000");
    HttpRequest *request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::GET);
    request->setTag("POST test");
    
    request->setUrl("http://192.168.2.152:8000/");
    std::string str = "username=123&password=123";
    //    request->setRequestData(str.c_str(), str.size());
    
    
    
    request->setResponseCallback(CC_CALLBACK_2(ModHttp::LogInCallback, this));
    HttpClient::getInstance()->send(request);
    request->release();
    
}

