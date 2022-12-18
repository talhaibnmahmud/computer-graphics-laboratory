#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <cerrno>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID;
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void Activate();
	void Delete();

	void CompileErrors(unsigned int shader, const char* type);
};
	

#endif // !SHADER_H

