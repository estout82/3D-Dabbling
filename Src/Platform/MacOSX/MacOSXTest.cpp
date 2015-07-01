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
}

MacOSXTest::~MacOSXTest()
{
    delete m_mesh;
    delete m_globalVao;
    delete m_window;
}

bool MacOSXTest::initalize()
{
    sf::ContextSettings cs;
    cs.majorVersion = 3;
    cs.minorVersion = 3;
    m_window = new sf::Window(sf::VideoMode(800, 600), "Title", sf::Style::Default, cs);
    
    glClearColor(0.5f, 0.8f, 0.97f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    
    std::vector<Vertex> vertecies;
    vertecies.push_back(Vertex(Vector3f(0.0f, 1.0f, -10.0f), Vector2f(0.5f, 1.0f)));
    vertecies.push_back(Vertex(Vector3f(-1.0f, -1.0f, -10.0f), Vector2f(0.0f, 0.0f)));
    vertecies.push_back(Vertex(Vector3f(1.0f, -1.0f, -10.0f), Vector2f(1.0f, 0.0f)));
    
    std::vector<unsigned int> indicies;
    indicies.push_back(0);
    indicies.push_back(1);
    indicies.push_back(2);
    
    
    Shader v(resourcePath("Shaders/vertex.s"), GL_VERTEX_SHADER);
    Shader f(resourcePath("Shaders/fragment.s"), GL_FRAGMENT_SHADER);
    
    m_globalVao = new VertexArrayObject();
    m_globalVao->create(v, f);
    
    m_mesh = new Mesh();
    m_mesh->createFromFile("duck.dae");
    
    a = 0.0f;
    
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
    
    m_globalVao->bind();
    
    a += 0.5f;
    
    ShaderProgram sp = m_globalVao->getShaderProgram();
    
    unsigned int worldMatrixLocation = sp.getUniformLocation("worldMatrix");
    
    Matrix4f perspective;
    perspective.initPerspective(800.0f / 600.0f, 90.0f, 0.1f, 1000.0f);
    
    Matrix4f translation;
    translation.initTranslation(Vector3f(0.0f, 0.0f, -a));
    
    sp.setUniformMatrix4f(worldMatrixLocation, perspective * translation);
    
    m_mesh->render();
    
    m_globalVao->unbind();
}

#endif // SHADY_PLATFORM_MAC_OSX