//
//  ShaderProgram.hpp
//  3D-Dabbling
//
//  Created by Eric Stoutenburg on 6/14/15.
//  Copyright (c) 2015 Eric Stoutenburg. All rights reserved.
//

#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include "Shader.hpp"
#include "Math.hpp"

class ShaderProgram
{
public:
	ShaderProgram();
    ShaderProgram(const std::string& vertexShaderPath,
                  const std::string& fragmentShaderPath);
    ShaderProgram(const Shader& vertexShader,
                  const Shader& fragmentShader);
	ShaderProgram(const ShaderProgram& sp);

	~ShaderProgram();

	bool create(const std::string& vertexShaderPath, 
		const std::string& fragmentShaderPath);

	bool create(const Shader& vertexShader,
		const Shader& fragmentShader);

	void use();

	void setUniformMatrix4f(int location,
		const Matrix4f& m);
	void setUniformVector4f(int location,
		const Vector4f& v);
	void setUniformVector3f(int location,
		const Vector3f& v);
	void setUniformVector2f(int location,
		const Vector2f& v);
	void setUniformFloat(int location,
		float f);
	void setUniformInt(int location,
		int i);

	int getUniformLocation(const std::string& name) const;

	inline unsigned int getHandle() const { return m_handle; }
	inline const Shader& getVertexShader() const { return m_vertex; }
	inline const Shader& getFragmentShader() const { return m_fragment; }
	inline const Shader& getGetometryShader() const { return m_geometry; }
    
    const ShaderProgram& operator=(const ShaderProgram& sp);

private:
	std::string getInfoLog() const;

    Shader m_vertex;
    Shader m_fragment;
    Shader m_geometry;
    
	unsigned int m_handle;
    
    unsigned* m_refCount;
    
    void dispose();
    
    void retainRef();
    void releaseRef();
};

#endif // SHADER_PROGRAM_HPP