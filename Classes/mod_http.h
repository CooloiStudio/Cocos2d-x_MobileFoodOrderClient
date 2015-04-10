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

    
public:
    
    int DownloadPicture(int img_id);
    void OnDownloadComplete(HttpClient *sender, HttpResponse *response);
    static void SetGetSocksDone(){get_socks_ = 0;}
    static void SetGetSocksing(){get_socks_ = -1;}
    static int GetSocksDone(){return get_socks_;}
};

#endif /* defined(__MobileFoodOrderClient__mod_http__) */
