#ifndef SHADER_H
#define SHADER_H

#include "pch.h"

// Function to read the contents of a file
std::string get_file_contents(const char* filename);


class Shader
{
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;

private:

	unsigned int mProgramID; 
	
public:

	Shader() {
		mProgramID = 0;
	}

	void load(const char* vertexFile, const char* fragmentFile);

	void use() const;
	void unload() const;

	
	unsigned int getProgramID();

	//Set Uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float v1);
	void SetUniform2f(const std::string& name, float f1, float f2);
	void SetUniform3fv(const std::string& name, glm::vec3 pos);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private: 
	int GetUniformLocation(const std::string& name);
};

#endif
