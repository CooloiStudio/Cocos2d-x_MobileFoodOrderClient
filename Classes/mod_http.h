//
//  mod_http.h
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/28/15.
//
//

#ifndef __MobileFoodOrderClient__mod_http__
#define __MobileFoodOrderClient__mod_http__

#include "iostream"
#include "cocos2d.h"
#include "network/HttpClient.h"

USING_NS_CC;
using namespace network;

class ModHttp : public Layer
{
public:
    ModHttp();
    ~ModHttp();
    bool init();
    static ModHttp* Create();
    static int get_socks_;
    static int go_int_;

    
public:
    
    int DownloadPicture(int img_id);
    void OnDownloadComplete(HttpClient *sender, HttpResponse *response);
    static void SetGetSocksDone(){get_socks_ = 0;}
    static void SetGetSocksing(){get_socks_ = -1;}
    static int GetSocksDone(){return get_socks_;}
    
    static void SetGoIntDone(){go_int_ = 0;}
    static void SetGoInting(){go_int_ = -1;}
    static int GetGoInt(){return go_int_;}
    
    
    void UserLogIn();
    void LogInCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    
    void UserLogOut();
    void UserTest();
    
};

#endif /* defined(__MobileFoodOrderClient__mod_http__) */
