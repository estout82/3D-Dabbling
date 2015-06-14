#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "Shader.h"
#include "Math.h"

class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const ShaderProgram& sp);

	~ShaderProgram();

	bool create(const std::string& vertexShaderPath, 
		const std::string& fragmentShaderPath);

	bool create(const Shader& vertexShader,
		const Shader& fragmentShader);

	void use();

	void dispose();

	void setUniformMatrix4f(unsigned int location, 
		const Matrix4f& m);
	void setUniformVector4f(unsigned int location, 
		const Vector4f& v);
	void setUniformVector3f(unsigned int location, 
		const Vector3f& v);
	void setUniformVector2f(unsigned int location, 
		const Vector2f& v);
	void setUniformFloat(unsigned int location, 
		float f);
	void setUniformInt(unsigned int location,
		int i);

	unsigned int getUniformLocation(const std::string& name) const;

	inline unsigned int getHandle() const { return m_handle; }
	inline const Shader& getVertexShader() const { return m_vertex; }
	inline const Shader& getFragmentShader() const { return m_fragment; }
	inline const Shader& getGetometryShader() const { return m_geometry; }

private:
	std::string getInfoLog() const;

	unsigned int m_handle;

	Shader m_vertex;
	Shader m_fragment;
	Shader m_geometry;
};

#endif