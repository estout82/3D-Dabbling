#include <GL/glew.h>
#include <iostream>
#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram() :
m_handle(NULL),
m_vertex(),
m_fragment(),
m_geometry()
{

}

ShaderProgram::ShaderProgram(const ShaderProgram& sp) :
m_handle(sp.m_handle),
m_vertex(sp.m_vertex),
m_fragment(sp.m_fragment),
m_geometry(sp.m_geometry)
{

}

ShaderProgram::~ShaderProgram()
{
	dispose();
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
	glGetShaderiv(m_handle, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		std::cout << "Error: unable to link a shader program: " << getInfoLog() << "." << std::endl;
		dispose();
		return false;
	}

	glValidateProgram(m_handle);

	glGetProgramiv(m_handle, GL_VALIDATE_STATUS, &status);

	if (status == GL_FALSE)
	{
		std::cout << "Error: unable to validate a shader program: " << getInfoLog() << "." << std::endl;
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

void ShaderProgram::dispose()
{
	if (m_handle)
	{
		glDeleteProgram(m_handle);
		m_handle = NULL;
	}
}

void ShaderProgram::setUniformMatrix4f(unsigned int location, 
	const Matrix4f& m)
{
	if (!location)
	{
		std::cout << "Error: unable to set a uniform Matrix4f because the location is NULL." << std::endl;
		return;
	}

	glUniformMatrix4fv(location, 1, GL_TRUE, &m.row[0][0]);
}

void ShaderProgram::setUniformVector4f(unsigned int location,
	const Vector4f& v)
{
	if (!location)
	{
		std::cout << "Error: unable to set a uniform Vector4f because the location is NULL." << std::endl;
		return;
	}

	glUniform4f(location, v.x, v.y, v.z, v.w);
}

void ShaderProgram::setUniformVector3f(unsigned int location, 
	const Vector3f& v)
{
	if (!location)
	{
		std::cout << "Error: unable to set a uniform Vector3f because the location is NULL." << std::endl;
		return;
	}

	glUniform3f(location, v.x, v.y, v.z);
}

void ShaderProgram::setUniformVector2f(unsigned int location, 
	const Vector2f& v)
{
	if (!location)
	{
		std::cout << "Error: unable to set a uniform Vector2f because the location is NULL." << std::endl;
		return;
	}

	glUniform2f(location, v.x, v.y);
}

void ShaderProgram::setUniformFloat(unsigned int location, 
	float f)
{
	if (!location)
	{
		std::cout << "Error: unable to set a uniform float because the location is NULL." << std::endl;
		return;
	}

	glUniform1f(location, f);
}

void ShaderProgram::setUniformInt(unsigned int location, 
	int i)
{
	if (!location)
	{
		std::cout << "Error: unable to set a uniform int because the location is NULL." << std::endl;
		return;
	}

	glUniform1i(location, i);
}

unsigned int ShaderProgram::getUniformLocation(const std::string& name) const
{
	int location = glGetUniformLocation(m_handle, name.c_str());

	if (location == -1)
	{
		std::cout << "Error: unable to get the location of the uniform '" << name << "'." << std::endl;
		return NULL;
	}

	return location;
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