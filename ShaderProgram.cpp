#include <GL/glew.h>
#include <iostream>
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() :
	m_handle(NULL),
	m_vertex(Shader()),
	m_fragment(Shader()),
	m_geometry(Shader())
{

}

ShaderProgram::ShaderProgram(const ShaderProgram& sp) :
	m_handle(sp.getHandle()),
	m_vertex(sp.getVertexShader()),
	m_fragment(sp.getFragmentShader()),
	m_geometry(sp.getGetometryShader())
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
		std::cout << "Unable to create a shader program." << std::endl;
		return false;
	}

	if (!m_vertex.getHandle())
	{
		std::cout << "Unable to attach a vertex shader to a program b/c the handle is NULL." << std::endl;
		return false;
	}

	else
		glAttachShader(m_handle, m_vertex.getHandle());

	if (!m_fragment.getHandle())
	{
		std::cout << "Unable to attach a fragment shader b/c the handle is NULL." << std::endl;
		return false;
	}

	else
		glAttachShader(m_handle, m_fragment.getHandle());

	if (!m_geometry.getHandle())
	{
		std::cout << "Unable to attach a geometry shader b/c the handle is NULL." << std::endl;
		//return false;
	}

	else
		glAttachShader(m_handle, m_geometry.getHandle());

	glLinkProgram(m_handle);

	int status;
	glGetShaderiv(m_handle, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		std::cout << "Unable to link a shader program: " << getInfoLog() << "." << std::endl;
		dispose();
		return false;
	}

	glValidateProgram(m_handle);

	glGetProgramiv(m_handle, GL_VALIDATE_STATUS, &status);

	if (status == GL_FALSE)
	{
		std::cout << "Unable to validate a shader program: " << getInfoLog() << "." << std::endl;
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
		std::cout << "Unable to use program because handle is NULL." << std::endl;
}

void ShaderProgram::dispose()
{
	if (m_handle)
	{
		glDeleteProgram(m_handle);
		m_handle = NULL;
	}
}

void ShaderProgram::setUniformMatrix4f(unsigned int location, const Matrix4f& m)
{
	if (!location)
	{
		std::cout << "Unable to set a uniform Matrix4f because the location is NULL." << std::endl;
		return;
	}

	glUniformMatrix4fv(location, 16, GL_FALSE, (const float*)&m);
}

void ShaderProgram::setUniformVector4f(unsigned int location, const Vector4f& v)
{
	if (!location)
	{
		std::cout << "Unable to set a uniform Vector4f because the location is NULL." << std::endl;
		return;
	}

	glUniform4f(location, v.x, v.y, v.z, v.w);
}

void ShaderProgram::setUniformVector3f(unsigned int location, const Vector3f& v)
{
	if (!location)
	{
		std::cout << "Unable to set a uniform Vector3f because the location is NULL." << std::endl;
		return;
	}

	glUniform3f(location, v.x, v.y, v.z);
}

void ShaderProgram::setUniformVector2f(unsigned int location, const Vector2f& v)
{
	if (!location)
	{
		std::cout << "Unable to set a uniform Vector2f because the location is NULL." << std::endl;
		return;
	}

	glUniform2f(location, v.x, v.y);
}

void ShaderProgram::setUniformFloat(unsigned int location, float f)
{
	if (!location)
	{
		std::cout << "Unable to set a uniform float because the location is NULL." << std::endl;
		return;
	}

	glUniform1f(location, f);
}

void ShaderProgram::setUniformInt(unsigned int location, int i)
{
	if (!location)
	{
		std::cout << "Unable to set a uniform int because the location is NULL." << std::endl;
		return;
	}

	glUniform1i(location, i);
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