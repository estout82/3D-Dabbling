//
//  WindowsTest.cpp
//  3D-Dabbling
//
//  Created by Eric Stoutenburg on 6/26/15.
//  Copyright (c) 2015 Eric Stoutenburg. All rights reserved.
//

#include "WindowsTest.hpp"

#ifdef SHADY_PLATFORM_WINDOWS

#include <iostream>
#include "Math.hpp"
#include "OpenGL.hpp"

#ifdef _DEBUG

#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "OpenGL32.lib")

#endif // _DEBUG

#ifdef _NDEBUG

#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "OpenGL32.lib")

#endif // _NDEBUG

WindowsTest::WindowsTest() :
m_window(NULL)
{
    std::cout << "Running on Windows." << std::endl;
}

WindowsTest::~WindowsTest()
{
    delete m_window;
}

bool WindowsTest::initalize()
{
    m_window = new sf::Window(sf::VideoMode(800, 600), "Title");
    
    // init glew
    if (m_window->isOpen())
    {
        int glewStatus = glewInit();
        
        if (glewStatus != GLEW_OK)
        {
            std::cout << "Error: Unable to initalize GLEW." << std::endl;
            
            window.close();
            dispose();
            return false;
        }
    }
    
    else
    {
        std::cout << "Error: Unable to create window." << std::endl;
        return false;
    }
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    Vertex vertecies[3] =
    {
        Vertex(Vector3<float>(0.0f, 1.0f, 0.0f), Vector2<float>(0.5f, 1.0f)),
        Vertex(Vector3<float>(-1.0f, -1.0f, 0.0f), Vector2<float>(0.0f, 0.0f)),
        Vertex(Vector3<float>(1.0f, -1.0f, 0.0f), Vector2<float>(1.0f, 0.0f))
    };

    return true;
}

void WindowsTest::run()
{
    while(m_window->isOpen())
    {
        sf::Event e;
        
        while(m_window->pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                m_window->close();
                return;
            }
        }
        
        update();
        render();
        
        m_window->display();
    }
}

void WindowsTest::update()
{
    
}

void WindowsTest::render()
{
    
}

#endif // SHADY_PLATFORM_WINDOWS