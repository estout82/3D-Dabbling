//
//  Buffer.h
//  3D-Dabbling
//
//  Created by Eric Stoutenburg on 6/27/15.
//  Copyright (c) 2015 Eric Stoutenburg. All rights reserved.
//

#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <vector>
#include <cassert>
#include "OpenGL.hpp"
#include "Math.hpp"

template<unsigned int target, typename type>
class Buffer
{
public:
    Buffer() :
    m_handle(NULL),
    m_numElements(0),
    m_refCount(new unsigned)
    {
        *m_refCount = 1;
    }
    
    Buffer(const std::vector<type>& data) :
    m_handle(NULL),
    m_numElements(0),
    m_refCount(new unsigned)
    {
        *m_refCount = 1;
        
        create(data);
    }
    
    Buffer(const Buffer<target, type>& copy) :
    m_handle(copy.m_handle),
    m_numElements(copy.m_numElements),
    m_refCount(copy.m_refCount)
    {
        retainRef();
    }
    
    ~Buffer()
    {
        releaseRef();
    }
    
    void create(const std::vector<type>& data)
    {
        dispose();
        
        m_numElements = (unsigned int)data.size();
        
        glGenBuffers(1, &m_handle);
        glBindBuffer(target, m_handle);
        glBufferData(target, sizeof(type) * m_numElements, &data[0], GL_STATIC_DRAW);
        glBindBuffer(target, NULL);
    }
    
    const Buffer<target, type>& operator=(const Buffer<target, type>& b)
    {
        releaseRef();
        
        m_handle = b.m_handle;
        m_numElements = b.m_numElements;
        m_refCount = b.m_refCount;
        
        retainRef();
    }
    
    void bind() const
    {
        glBindBuffer(target, m_handle);
    }
    
    void unbind() const
    {
        glBindBuffer(target, NULL);
    }
    
private:
    unsigned int m_handle;
    unsigned int m_numElements;
    
    unsigned* m_refCount;
    
    void dispose()
    {
        if (m_handle)
        {
            glDeleteBuffers(1, &m_handle);
            m_handle = NULL;
            m_numElements = 0;
        }
    }
    
    void retainRef()
    {
        assert(m_refCount);
        *m_refCount += 1;
    }
    
    void releaseRef()
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
};

typedef Buffer<GL_ARRAY_BUFFER, Vertex> VertexBuffer;
typedef Buffer<GL_ELEMENT_ARRAY_BUFFER, unsigned int> IndexBuffer;

#endif // BUFFER_HPP