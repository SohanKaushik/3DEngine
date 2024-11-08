#include "Shader.h"
#include <string>
#include <cerrno>

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	else {
		// Buffer for error message
		char buffer[10];
		strerror_s(buffer, sizeof(buffer), errno);
		std::cerr << "Error: Unable to open file " << filename << " - " << buffer << std::endl;
		throw std::runtime_error("Error opening file " + std::string(filename) + ": " + buffer);
	}
}



// Constructor that build the Shader Program from 2 different shaders


Shader::Shader(const char* vertexFile, const char* fragmentFile)
{



	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



}

// Activates the Shader Program
void Shader::Bind() const
{
	glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Unbind() const
{
	glUseProgram(ID);
}


void Shader::SetUniform1i(const std::string& name, int value) {
	GLint location = glGetUniformLocation(ID, name.c_str());
	if (location == -1) {
		std::cerr << "Uniform '" << name << "' not found in shader program.\n";
	}
	else {
		glUniform1i(location, value);
	}
}



