//
//  MacOSXTest.cpp
//  3D-Dabbling
//
//  Created by Eric Stoutenburg on 6/26/15.
//  Copyright (c) 2015 Eric Stoutenburg. All rights reserved.
//

#include "MacOSXTest.hpp"

#ifdef SHADY_PLATFORM_MAC_OSX

#include <iostream>
#include "MacOSXTest.hpp"
#include "MacOSX.hpp"
#include "Math.hpp"
#include "OpenGL.hpp"

MacOSXTest::MacOSXTest() :
m_window(NULL)
{
    std::cout << "Running on MacOSX." << std::endl;
    
    angle = 0.0f;
}

MacOSXTest::~MacOSXTest()
{
    delete m_texture;
    delete m_vao;
    delete m_window;
}

bool MacOSXTest::initalize()
{
    sf::ContextSettings cs;
    cs.majorVersion = 3;
    cs.minorVersion = 3;
    m_window = new sf::Window(sf::VideoMode(800, 600), "Title", sf::Style::Default, cs);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    
    std::vector<Vertex> vertecies;
    vertecies.push_back(Vertex(Vector3f(0.0f, 1.0f, -5.0f), Vector2f(0.5f, 1.0f)));
    vertecies.push_back(Vertex(Vector3f(-1.0f, -1.0f, -5.0f), Vector2f(0.0f, 0.0f)));
    vertecies.push_back(Vertex(Vector3f(1.0f, -1.0f, -5.0f), Vector2f(1.0f, 0.0f)));
    
    std::vector<unsigned int> indicies;
    indicies.push_back(0);
    
    Shader v(resourcePath("Shaders/vertex.s"), GL_VERTEX_SHADER);
    Shader f(resourcePath("Shaders/fragment.s"), GL_FRAGMENT_SHADER);
    
    m_vao = new VertexArrayObject();
    m_vao->create(vertecies, indicies, v, f);
    
    m_texture = new Texture(resourcePath("image.png"));
    
    return true;
}

void MacOSXTest::run()
{
    while(m_window->isOpen())
    {
        sf::Event e;
        
        while(m_window->pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                return;
            }
        }
        
        update();
        render();
        
        m_window->display();
    }
}

void MacOSXTest::update()
{
    
}

void MacOSXTest::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    ShaderProgram sp = m_vao->getShaderProgram();
    
    unsigned int matrixLocation = sp.getUniformLocation("worldMatrix");
    
    angle += 1.0f;
    
    Matrix4f p;
    p.initPerspective(800.0f / 600.0f, 90.0f, 0.1f, 100.0f);
    
    Matrix4f r;
    r.initRotationXYZ(angle * 0.3f, Vector3f(0.0f, 0.0f, 1.0f));
    
    sp.setUniformMatrix4f(matrixLocation, (p * r));
    
    m_vao->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

#endif // SHADY_PLATFORM_MAC_OSX