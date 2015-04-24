//
//  mod_config_json.h
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 4/22/15.
//
//

#ifndef __MobileFoodOrderClient__mod_config_json__
#define __MobileFoodOrderClient__mod_config_json__

#include "cocos2d.h"
#include "iostream"

class ConfigJson
{
private:
    
    static std::string config_ip_;
    static std::string config_port_;
    static int boom_;
    
public:
    
    static std::string GetConfigIp(){return config_ip_;}
    static std::string GetConfigPort(){return config_port_;}
    static int GetBoomNum(){return boom_;}
    
    static void SetConfigIp(std::string ip){config_ip_ = ip;}
    static void SetConfigPort(std::string port){config_port_ = port;}
    
};

#endif /* defined(__MobileFoodOrderClient__mod_config_json__) */
