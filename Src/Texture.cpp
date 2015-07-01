//
//  Texture.cpp
//  3D-Dabbling
//
//  Created by Eric Stoutenburg on 6/14/15.
//  Copyright (c) 2015 Eric Stoutenburg. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include "3rdParty/stb_image.h"
#include "OpenGL.hpp"
#include "Texture.hpp"

Texture::Texture() :
m_handle(NULL),
m_refCount(new unsigned)
{
	*m_refCount = 1;
}

Texture::Texture(const std::string& path) :
m_handle(NULL),
m_refCount(new unsigned)
{
	*m_refCount = 1;

	loadFromFile(path);
}

Texture::Texture(const Texture& t) :
m_handle(t.getHandle()),
m_refCount(t.getRefCount())
{
	assert(m_refCount);
	*m_refCount += 1;
}

Texture::~Texture()
{
	dispose();
}

bool Texture::loadFromFile(const std::string& path)
{
    int width, height, channels;
    unsigned char* pixels;

	pixels = stbi_load(path.c_str(), &width, &height, &channels, 4);

	if (!pixels)
	{
		std::cout << "Unable to load image file " << path << "." << std::endl;
		stbi_image_free(pixels);
		return false;
	}

	bool r = create(width, height, channels, pixels);
	stbi_image_free(pixels);

	return r;
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_handle);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

const Texture& Texture::operator=(const Texture& t)
{
	dispose();

	m_handle = t.getHandle();
	m_refCount = t.getRefCount();

	assert(m_refCount);
	*m_refCount += 1;

	return *this;
}

bool Texture::create(int width,
	int height,
	int channels,
	unsigned char* pixels)
{
	glGenTextures(1, &m_handle);

	if (!m_handle)
	{
		std::cout << "Unable to create a texture." << std::endl; 
		return false;
	}

	bind();

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int format = 0;

	if (channels == 3)
		format = GL_RGB;

	else if (channels == 4)
		format = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D,
		0,
		format,
		width,
		height,
		NULL,
		format,
		GL_UNSIGNED_BYTE,
		pixels);

	return true;
}

void Texture::dispose()
{
	assert(m_refCount && *m_refCount > 0);
	*m_refCount -= 1;

	if (*m_refCount == 0)
	{
		deleteTexture();

		delete m_refCount;
		m_refCount = NULL;
	}
}

void Texture::deleteTexture()
{
	if (m_handle)
	{
		glDeleteTextures(1, &m_handle);
		m_handle = NULL;
	}
}