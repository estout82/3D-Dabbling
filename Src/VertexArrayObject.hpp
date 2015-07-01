//
//  VertexArray.h
//  3D-Dabbling
//
//  Created by Eric Stoutenburg on 6/26/15.
//  Copyright (c) 2015 Eric Stoutenburg. All rights reserved.
//

#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include <vector>
#include "ShaderProgram.hpp"
#include "Buffer.hpp"

// TODO: add validation system to prevent acessing NULL buffers

class VertexArrayObject
{
public:
    VertexArrayObject();
    VertexArrayObject(const VertexArrayObject& v);

    ~VertexArrayObject();
    
    bool create(const Shader& vertexShader,
                const Shader& fragmentShader,
                const Shader& geometryShader = Shader());
    
    void reset();
    
    void bind() const;
    void unbind() const;
    
    const VertexArrayObject& operator=(const VertexArrayObject& v);
    
    inline const ShaderProgram& getShaderProgram() const
    {
        return m_program;
    }
    
private:
    ShaderProgram m_program;
    
    unsigned int m_handle;
    
    unsigned* m_refCount;
    
    void dispose();
    
    void retainRef();
    void releaseRef();
};

#endif
