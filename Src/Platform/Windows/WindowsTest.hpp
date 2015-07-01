//
//  WindowsTest.hpp
//  3D-Dabbling
//
//  Created by Eric Stoutenburg on 6/26/15.
//  Copyright (c) 2015 Eric Stoutenburg. All rights reserved.
//

#ifndef WINDOWS_TEST_HPP
#define WINDOWS_TEST_HPP

#include <SFML/Window.hpp>
#include "Main.hpp"

class WindowsTest : public Test
{
public:
    WindowsTest();
    
    virtual ~WindowsTest();
    
    virtual bool initalize();
    virtual void run();
    
private:
    sf::Window* m_window;
    
    void update();
    void render();
};

#endif
