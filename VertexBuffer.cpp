#include <GL/glew.h>
#include "VertexBuffer.h"
#include "Null.h"

VertexBuffer::VertexBuffer() :
	m_handle(NULL),
	m_numVertecies(0)
{
	
}

VertexBuffer::VertexBuffer(const Vertex* vertecies, unsigned int num) :
	m_handle(NULL),
	m_numVertecies(num)
{
	create(vertecies, num);
}

VertexBuffer::~VertexBuffer()
{
	dispose();
}

unsigned int VertexBuffer::create(const Vertex* vertecies, unsigned int num)
{
	if (m_handle)
		dispose();

	glGenBuffers(1, &m_handle);
	glBindBuffer(GL_ARRAY_BUFFER, m_handle);
	glBufferData(GL_ARRAY_BUFFER, num * sizeof(Vertex), &vertecies[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	return m_handle;
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_handle);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::reset()
{
	// TODO: implement method
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