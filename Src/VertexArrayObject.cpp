//
//  VertexArray.cpp
//  3D-Dabbling
//
//  Created by Eric Stoutenburg on 6/26/15.
//  Copyright (c) 2015 Eric Stoutenburg. All rights reserved.
//

#include <cassert>
#include <iostream>
#include "VertexArrayObject.hpp"
#include "OpenGL.hpp"
#include "Platform/MacOSX/MacOSX.hpp"

VertexArrayObject::VertexArrayObject() :
m_program(),
m_vboHandle(NULL),
m_iboHandle(NULL),
m_handle(NULL),
m_refCount(new unsigned)
{
    *m_refCount = 1;
    
    std::cout << m_refCount << " - " << *m_refCount << std::endl;
}

VertexArrayObject::VertexArrayObject(const VertexArrayObject& v) :
m_program(v.m_program),
m_vboHandle(v.m_vboHandle),
m_iboHandle(v.m_iboHandle),
m_handle(v.m_handle),
m_refCount(v.m_refCount)
{
    retainRef();
}

VertexArrayObject::~VertexArrayObject()
{
    releaseRef();
}

void VertexArrayObject::create(const std::vector<Vertex>& vertecies,
                               const std::vector<unsigned int>& indicies,
                               const Shader& vertexShader,
                               const Shader& fragmentShader,
                               const Shader& geometryShader)
{
    if (m_handle)
        dispose();
    
    glGenVertexArrays(1, &m_handle);
    glBindVertexArray(m_handle);
    
    m_program.create(vertexShader, fragmentShader);
    m_program.use();
    
    glGenBuffers(1, &m_vboHandle);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboHandle);
    glBufferData(GL_ARRAY_BUFFER, vertecies.size() * sizeof(Vertex), &vertecies[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &m_iboHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int),    &indicies[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12);
    
    glBindVertexArray(0);
}

void VertexArrayObject::bind() const
{
    glBindVertexArray(m_handle);
}

void VertexArrayObject::unbind() const
{
    glBindVertexArray(0);
}

void VertexArrayObject::dispose()
{
    if (m_handle)
    {
        glDeleteVertexArrays(1, &m_handle);
        m_handle = NULL;
    }
    
    if (m_vboHandle)
    {
        glDeleteBuffers(1, &m_vboHandle);
        m_vboHandle = NULL;
    }
    
    if (m_iboHandle)
    {
        glDeleteBuffers(1, &m_iboHandle);
        m_iboHandle = NULL;
    }
}

void VertexArrayObject::retainRef()
{
    assert(m_refCount);
    *m_refCount += 1;
}

void VertexArrayObject::releaseRef()
{
    assert(m_refCount && *m_refCount > 0);
    *m_refCount -= 1;
    
    if (*m_refCount == 0)
    {
        dispose();
        delete m_refCount;
        m_refCount = NULL;
    }
}