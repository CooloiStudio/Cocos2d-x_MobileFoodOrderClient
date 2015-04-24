//
//  custom_string.cpp
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 4/24/15.
//
//

#include "custom_string.h"


std::string custom_string::int_to_string(int value)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    std::ostringstream os;
    os << value;
    return os.str();
    
#else
    
    return std::to_string(value);
    
#endif
}