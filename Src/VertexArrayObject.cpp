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
m_handle(NULL),
m_refCount(new unsigned)
{
    *m_refCount = 1;
}

VertexArrayObject::VertexArrayObject(const VertexArrayObject& v) :
m_program(v.m_program),
m_handle(v.m_handle),
m_refCount(v.m_refCount)
{
    retainRef();
}

VertexArrayObject::~VertexArrayObject()
{
    releaseRef();
}

bool VertexArrayObject::create(const Shader& vertexShader,
                               const Shader& fragmentShader,
                               const Shader& geometryShader)
{
    dispose();
    
    glGenVertexArrays(1, &m_handle);
    
    if (!m_handle)
        return false;
    
    glBindVertexArray(m_handle);
    
    m_program.create(vertexShader, fragmentShader);
    m_program.use();
    
    glBindVertexArray(0);
    
    return true;
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