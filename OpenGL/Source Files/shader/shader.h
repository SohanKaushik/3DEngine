#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <glm/gtc/matrix_transform.hpp>
#include <unordered_map>

// Function to read the contents of a file
std::string get_file_contents(const char* filename);


class Shader
{
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;
	
public:
	
	GLuint ID; // Reference ID of the Shader Program

	// Constructor that builds the Shader Program from two shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activates the Shader Program
	void Bind() const;
	// Deletes the Shader Program
	void Unbind() const;

	unsigned int getProgramID();

	

	bool isActive() const;
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
