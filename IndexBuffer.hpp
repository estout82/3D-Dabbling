#ifndef INDEX_BUFFER_HPP
#define INDEX_BUFFER_HPP

class IndexBuffer
{
public:
	IndexBuffer();
	IndexBuffer(unsigned int* indicies,
		unsigned int num);
	IndexBuffer(const IndexBuffer& i);

	~IndexBuffer();

	void bind() const;
	void unbind() const;

	void reset();

	const IndexBuffer& operator=(const IndexBuffer& i);

	inline unsigned int getHandle() const { return m_handle; }
	inline unsigned int getNumIndicies() const { return m_numIndicies; }

private:
	unsigned int m_handle;
	unsigned int m_numIndicies;

	void dispose();

	unsigned* m_refCount;

	void retainRef();
	void releaseRef();
};

#endif