#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "Math.h"
#include <GL/glew.h>

class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(const Vertex* vertecies, unsigned int num);

	~VertexBuffer();

	unsigned int create(const Vertex* vertecies, unsigned int num);

	void updateVertecies(const Vertex* vertecies);

	void bind() const;
	void unbind() const;

	void reset(); // TODO: implement 

	void dispose();

	inline unsigned int getHandle() const { return m_handle; }
	inline unsigned int getNumVertecies() const { return m_numVertecies; }

private:
	unsigned int m_handle;
	unsigned int m_numVertecies;
};

#endif