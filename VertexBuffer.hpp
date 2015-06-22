#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include "Math.hpp"
#include <GL/glew.h>

class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(const Vertex* vertecies, 
		unsigned int num);
	VertexBuffer(const VertexBuffer& v);

	~VertexBuffer();

	void bind() const;
	void unbind() const;

	void reset(); 

	const VertexBuffer& operator=(const VertexBuffer& v);

	inline unsigned int getHandle() const { return m_handle; }
	inline unsigned int getNumVertecies() const { return m_numVertecies; }

private:
	unsigned int m_handle;
	unsigned int m_numVertecies;

	void dispose();

	unsigned* m_refCount;

	void retainRef();
	void releaseRef();
};

#endif // VERTEX_BUFFER_HPP