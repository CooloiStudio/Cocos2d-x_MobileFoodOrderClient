//
//  Info.h
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 3/21/15.
//
//

#ifndef __MobileFoodOrderClient__Info__
#define __MobileFoodOrderClient__Info__

#ifndef MobileFoodOrderClient_Info_h
#define MobileFoodOrderClient_Info_h

#include "iostream"
#include "cocos2d.h"

USING_NS_CC;

class LogInfo : public Ref
{
private:
    static int login;

public:
    static int GetLogIn(){return login;}
    static void SetLogIn(){login = 0;}
    static void SetLogOut(){login = -1;}


};


#endif

#endif /* defined(__MobileFoodOrderClient__Info__) */
