//
//  ShaderProgram.cpp
//  3D-Dabbling
//
//  Created by Eric Stoutenburg on 6/14/15.
//  Copyright (c) 2015 Eric Stoutenburg. All rights reserved.
//

#include <iostream>
#include "ShaderProgram.hpp"
#include "OpenGL.hpp"

ShaderProgram::ShaderProgram() :
m_vertex(),
m_fragment(),
m_geometry(),
m_handle(NULL),
m_refCount(new unsigned)
{
    *m_refCount = 1;
}

ShaderProgram::ShaderProgram(const std::string& vertexShaderPath,
                             const std::string& fragmentShaderPath) :
m_vertex(),
m_fragment(),
m_geometry(),
m_handle(NULL),
m_refCount(new unsigned)
{
    *m_refCount = 1;
    
    create(Shader(vertexShaderPath, GL_VERTEX_SHADER), Shader(fragmentShaderPath, GL_FRAGMENT_SHADER));
}

ShaderProgram::ShaderProgram(const Shader& vertexShader,
                             const Shader& fragmentShader) :
m_vertex(),
m_fragment(),
m_geometry(),
m_handle(NULL),
m_refCount(new unsigned)
{
    *m_refCount = 1;
    
    create(vertexShader, fragmentShader);
}

ShaderProgram::ShaderProgram(const ShaderProgram& sp) :
m_handle(sp.m_handle),
m_vertex(sp.m_vertex),
m_fragment(sp.m_fragment),
m_geometry(sp.m_geometry),
m_refCount(sp.m_refCount)
{
    retainRef();
}

ShaderProgram::~ShaderProgram()
{
    releaseRef();
}

bool ShaderProgram::create(const std::string& vertexShaderPath,
	const std::string& fragmentShaderPath)
{
	return create(Shader(vertexShaderPath, GL_VERTEX_SHADER),
		Shader(fragmentShaderPath, GL_FRAGMENT_SHADER));
}

bool ShaderProgram::create(const Shader& vertexShader,
	const Shader& fragmentShader)
{
    if (m_handle)
        dispose();
    
	m_vertex = vertexShader;
	m_fragment = fragmentShader;

	m_handle = glCreateProgram();

	if (!m_handle)
	{
		std::cout << "Error: unable to create a shader program." << std::endl;
		return false;
	}

	if (!m_vertex.getHandle())
	{
		std::cout << "Error: unable to attach a vertex shader to a program b/c the handle is NULL." << std::endl;
		return false;
	}

	else
		glAttachShader(m_handle, m_vertex.getHandle());

	if (!m_fragment.getHandle())
	{
		std::cout << "Error: unable to attach a fragment shader b/c the handle is NULL." << std::endl;
		return false;
	}

	else
		glAttachShader(m_handle, m_fragment.getHandle());

	if (!m_geometry.getHandle())
	{
		std::cout << "Error: unable to attach a geometry shader b/c the handle is NULL." << std::endl;
		//return false;
	}

	else
		glAttachShader(m_handle, m_geometry.getHandle());

	glLinkProgram(m_handle);

	int status;
	glGetProgramiv(m_handle, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		std::cout << "Error: unable to link a shader program: " << getInfoLog();
		dispose();
		return false;
	}

	glValidateProgram(m_handle);
	glGetProgramiv(m_handle, GL_VALIDATE_STATUS, &status);

	if (status == GL_FALSE)
	{
		std::cout << "Error: unable to validate a shader program: " << getInfoLog();
		dispose();
		return false;
	}

	return true;
}

void ShaderProgram::use()
{
	if (m_handle)
		glUseProgram(m_handle);

	else
		std::cout << "Error: unable to use program because handle is NULL." << std::endl;
}

void ShaderProgram::setUniformMatrix4f(int location,
	const Matrix4f& m)
{
	if (location == -1)
	{
		std::cout << "Error: unable to set a uniform Matrix4f because the location is NULL." << std::endl;
		return;
	}

	glUniformMatrix4fv(location, 1, GL_TRUE, &m.row[0][0]);
}

void ShaderProgram::setUniformVector4f(int location,
	const Vector4f& v)
{
	if (location == -1)
	{
		std::cout << "Error: unable to set a uniform Vector4f because the location is NULL." << std::endl;
		return;
	}

	glUniform4f(location, v.x, v.y, v.z, v.w);
}

void ShaderProgram::setUniformVector3f(int location,
	const Vector3f& v)
{
	if (location == -1)
	{
		std::cout << "Error: unable to set a uniform Vector3f because the location is NULL." << std::endl;
		return;
	}

	glUniform3f(location, v.x, v.y, v.z);
}

void ShaderProgram::setUniformVector2f(int location,
	const Vector2f& v)
{
	if (location == -1)
	{
		std::cout << "Error: unable to set a uniform Vector2f because the location is NULL." << std::endl;
		return;
	}

	glUniform2f(location, v.x, v.y);
}

void ShaderProgram::setUniformFloat(int location,
	float f)
{
	if (location == -1)
	{
		std::cout << "Error: unable to set a uniform float because the location is NULL." << std::endl;
		return;
	}

	glUniform1f(location, f);
}

void ShaderProgram::setUniformInt(int location,
	int i)
{
	if (location ==  -1)
	{
		std::cout << "Error: unable to set a uniform int because the location is NULL." << std::endl;
		return;
	}

	glUniform1i(location, i);
}

int ShaderProgram::getUniformLocation(const std::string& name) const
{
	int location = glGetUniformLocation(m_handle, name.c_str());

	if (location == -1)
	{
		std::cout << "Error: unable to get the location of the uniform '" << name << "'." << std::endl;
		return -1;
	}

	return static_cast<unsigned int>(location);
}

const ShaderProgram& ShaderProgram::operator=(const ShaderProgram &sp)
{
    releaseRef();
    
    m_vertex = sp.m_vertex;
    m_fragment = sp.m_fragment;
    m_geometry = sp.m_geometry;
    m_handle = sp.m_handle;
    m_refCount = sp.m_refCount;
    
    retainRef();
    
    return *this;
}

void ShaderProgram::dispose()
{
    if (m_handle)
    {
        if (m_vertex.getHandle())
            glDetachShader(m_handle, m_vertex.getHandle());
        
        if (m_fragment.getHandle())
            glDetachShader(m_handle, m_fragment.getHandle());
        
        if (m_geometry.getHandle())
            glDetachShader(m_handle, m_geometry.getHandle());
        
        glDeleteProgram(m_handle);
    }
}

void ShaderProgram::retainRef()
{
    assert(m_refCount);
    *m_refCount += 1;
}

void ShaderProgram::releaseRef()
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

std::string ShaderProgram::getInfoLog() const
{
	int infoLogLen;
	glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &infoLogLen);

	char* infoLog = new char[infoLogLen + 1];
	glGetProgramInfoLog(m_handle, infoLogLen, NULL, infoLog);

	std::string s(infoLog);
	delete[] infoLog;

	return s;
}