#include <GL/glew.h>
#include <iostream>
#include <cassert>
#include "IndexBuffer.hpp"
#include "Main.hpp"

IndexBuffer::IndexBuffer() :
m_handle(NULL),
m_numIndicies(0),
m_refCount(new unsigned)
{
	*m_refCount = 1;
}

IndexBuffer::IndexBuffer(unsigned int* indicies, unsigned int num) :
m_handle(NULL),
m_numIndicies(num),
m_refCount(new unsigned)
{
	*m_refCount = 1;

	glGenBuffers(1, &m_handle);

	if (!m_handle)
	{
		std::cout << "Error: unable to create an index buffer." << std::endl;
		return;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num * sizeof(unsigned int), indicies, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
}

IndexBuffer::IndexBuffer(const IndexBuffer& i) :
m_handle(i.m_handle),
m_numIndicies(i.m_numIndicies),
m_refCount(i.m_refCount)
{
	retainRef();
}

IndexBuffer::~IndexBuffer()
{
	releaseRef();
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
}

void IndexBuffer::reset()
{
	releaseRef();
}

const IndexBuffer& IndexBuffer::operator=(const IndexBuffer& i)
{
	releaseRef();

	m_handle = i.m_handle;
	m_numIndicies = i.m_numIndicies;
	m_refCount = i.m_refCount;

	retainRef();

	return *this;
}

void IndexBuffer::dispose()
{
	if (m_handle)
	{
		glDeleteBuffers(1, &m_handle);
		m_handle = NULL;
		m_numIndicies = 0;
	}
}

void IndexBuffer::retainRef()
{
	assert(m_refCount);
	*m_refCount++;
}

void IndexBuffer::releaseRef()
{
	assert(m_refCount && *m_refCount > 0);
	*m_refCount--;

	if (*m_refCount == 0)
	{
		dispose();
		delete m_refCount;
		m_refCount = NULL;
	}
}