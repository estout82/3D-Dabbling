#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture
{
public:
	Texture();
	Texture(const std::string& path);

	Texture(const Texture& t);

	~Texture();

	bool loadFromFile(const std::string& path);

	void bind() const;
	void unbind() const;

	const Texture& operator=(const Texture& t);

	inline unsigned int getHandle() const { return m_handle; }
	inline unsigned* getRefCount() const { return m_refCount; }

private:
	bool create(int width,
		int height,
		int channels,
		unsigned char* pixels);

	void dispose();
	void deleteTexture();

	unsigned int m_handle;
	unsigned* m_refCount;
};

#endif