#include <GL/glew.h>
#include <iostream>
#include <cassert>
#include "VertexBuffer.hpp"
#include "Main.hpp"

VertexBuffer::VertexBuffer() :
m_handle(NULL),
m_numVertecies(0),
m_refCount(new unsigned)
{
	*m_refCount = 1;
}

VertexBuffer::VertexBuffer(const Vertex* vertecies, unsigned int num) :
m_handle(NULL),
m_numVertecies(num),
m_refCount(new unsigned)
{
	*m_refCount = 1;

	if (m_handle)
		dispose();

	glGenBuffers(1, &m_handle);

	if (!m_handle)
	{
		std::cout << "Error: unable to create a vertex buffer." << std::endl;
		m_numVertecies = 0;
		return;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_handle);
	glBufferData(GL_ARRAY_BUFFER, num * sizeof(Vertex), &vertecies[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

VertexBuffer::VertexBuffer(const VertexBuffer& v) :
m_handle(v.m_handle),
m_numVertecies(v.m_numVertecies),
m_refCount(v.m_refCount)
{
	retainRef();
}

VertexBuffer::~VertexBuffer()
{
	releaseRef();
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_handle);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

void VertexBuffer::reset()
{
	releaseRef();
}

const VertexBuffer& VertexBuffer::operator=(const VertexBuffer& v)
{
	releaseRef();

	m_handle = v.m_handle;
	m_numVertecies = v.m_numVertecies;
	m_refCount = v.m_refCount;

	retainRef();

	return *this;
}

void VertexBuffer::dispose()
{
	if (m_handle)
	{
		glDeleteBuffers(1, &m_handle);
		m_handle = NULL;
		m_numVertecies = 0;
	}
}

void VertexBuffer::retainRef()
{
	assert(m_refCount);
	*m_refCount++;
}

void VertexBuffer::releaseRef()
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