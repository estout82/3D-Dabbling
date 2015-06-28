//
//  MacOSXTest.h
//  3D-Dabbling
//
//  Created by Eric Stoutenburg on 6/26/15.
//  Copyright (c) 2015 Eric Stoutenburg. All rights reserved.
//

#ifndef MAC_OSX_TEST_HPP
#define MAC_OSX_TEST_HPP

#include <SFML/Window.hpp>
#include "Main.hpp"
#include "ShaderProgram.hpp"
#include "VertexArrayObject.hpp"
#include "Texture.hpp"

class MacOSXTest : public Test
{
public:
    MacOSXTest();
    
    virtual ~MacOSXTest();
    
    virtual bool initalize();
    virtual void run();
    
private:
    sf::Window* m_window;
    
    Texture* m_texture;
    VertexArrayObject* m_vao;
    
    void update();
    void render();
};

#endif // MAC_OSX_TEST_HPP