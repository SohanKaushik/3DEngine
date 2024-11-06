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
	void Activate();
	// Deletes the Shader Program
	void Delete();
};

#endif
