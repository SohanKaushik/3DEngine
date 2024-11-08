#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <iostream>
#include <cerrno>

// Function to read the contents of a file
std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID; // Reference ID of the Shader Program

	// Constructor that builds the Shader Program from two shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activates the Shader Program
	void Bind() const;
	// Deletes the Shader Program
	void Unbind() const;

	//Set Uniforms
	void SetUniform1i(const std::string& name, int value);
	//void SetUnifrom1f(const std::string& name, float value);
	//void SetUnifrom4i(const std::string& name, float v0, float v1, float v2, float v3);

	//int GetUniformLocation(const std::string& name);

};

#endif
