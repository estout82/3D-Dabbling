#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader
{
public:
	Shader();
	Shader(const std::string& path, unsigned int type);

	Shader(const Shader& s);

	~Shader();

	bool create(const std::string& code, unsigned int type);
	bool createFromFile(const std::string& path, unsigned int type);

	const Shader& operator=(const Shader& r);

	inline unsigned int getHandle() const { return m_handle; }
	inline unsigned* getRefCount() const { return m_refCount; }

private:
	std::string getInfoLog() const;
	std::string readFile(const std::string& path) const;

	void dispose();
	void deleteShader();

	unsigned int m_handle;
	unsigned* m_refCount;
};

#endif