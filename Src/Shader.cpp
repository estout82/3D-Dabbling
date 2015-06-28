#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>
#include "OpenGL.hpp"
#include "Shader.hpp"

Shader::Shader() :
m_handle(NULL),
m_refCount(new unsigned)
{
	*m_refCount = 1;
}

Shader::Shader(const std::string& path, 
	unsigned int type) :
m_handle(NULL),
m_refCount(new unsigned)
{
	*m_refCount = 1;

	create(readFile(path), type);
}

Shader::Shader(const Shader& s) :
m_handle(s.getHandle()),
m_refCount(s.getRefCount())
{
	assert(m_refCount);
	*m_refCount += 1;
}

Shader::~Shader()
{
	dispose();
}

bool Shader::createFromFile(const std::string& path, 
	unsigned int type)
{
	return create(readFile(path).c_str(), type);
}

const Shader& Shader::operator=(const Shader& s)
{
	dispose(); // update ref cnt & dispose of old handle if needed

	m_handle = s.getHandle();
	m_refCount = s.getRefCount();

	assert(m_refCount);
	*m_refCount += 1;

	return *this;
}

bool Shader::create(const std::string& code, 
	unsigned int type)
{
	m_handle = glCreateShader(type);

	if (!m_handle)
	{
		std::cout << "Unable to create a shader." << std::endl;
		return false;
	}

	const char* src = code.c_str();
	glShaderSource(m_handle, 1, (const char**)&src, NULL);

	glCompileShader(m_handle);

	int status = 0;
	glGetShaderiv(m_handle, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		std::cout << "Unable to compile a shader: " << getInfoLog() << std::endl;
		deleteShader();
		return false;
	}

	return true;
}

std::string Shader::getInfoLog() const
{
	if (!m_handle)
	{
		std::cout << "Unable to get shader info log becease shader handle is NULL." << std::endl;
		return "\0";
	}

	int infoLogLen;
	glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &infoLogLen);

	char* infoLog = new char[infoLogLen + 1];
	glGetShaderInfoLog(m_handle, infoLogLen, NULL, infoLog);
	infoLog[infoLogLen] = '\0';

	std::string s(infoLog);
	delete[] infoLog;

	return s;
}

std::string Shader::readFile(const std::string& path) const
{
	std::ifstream f;
	f.open(path.c_str(), std::ios::in | std::ios::binary);

	if (!f.is_open())
	{
		std::cout << "Unable to open shader file: " << path << "." << std::endl;
		return "\0";
	}

	std::stringstream stream;
	stream << f.rdbuf() << "\0";

	return stream.str();
}

void Shader::dispose()
{
	assert(m_refCount && *m_refCount > 0);
	*m_refCount -= 1;

	if (*m_refCount == 0)
	{
		deleteShader();

		delete m_refCount;
		m_refCount = NULL;
	}
}

void Shader::deleteShader()
{
	if (m_handle)
	{
		glDeleteShader(m_handle);
		m_handle = NULL;
	}
}