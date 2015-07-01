//
//  Main.hpp
//  3D-Dabbling
//
//  Created by Eric Stoutenburg on 6/22/15.
//  Copyright (c) 2015 Eric Stoutenburg. All rights reserved.
//

#ifndef MAIN_HPP
#define MAIN_HPP

//#define SHADY_PLATFORM_WINDOWS
#define SHADY_PLATFORM_MAC_OSX

class Test
{
public:
    Test() {}
    
    virtual ~Test() {}
    
    virtual bool initalize() = 0;
    virtual void run() = 0;
    
private:
};

#endif