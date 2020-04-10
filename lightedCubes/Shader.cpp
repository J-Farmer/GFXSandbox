#include "Shader.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

//Shader constructor. 
Shader::Shader(const char* vertex_path, const char* fragment_path, const char* geometry_path)
{
	this->vertex_path = vertex_path;
	this->fragment_path = fragment_path;
	this->geom_path = geometry_path; 

	loadComplieShaders(vertex_path, fragment_path, geometry_path);
}

//This will compile the shader at shaderID. Pass it the unique ID for the shader you want. Takes in the filepath and the shader id as parameters.
GLint compileShader(const char* filePath, GLuint shaderID) 
{
	std::string shaderCode;

	std::ifstream fileStream(filePath, std::ios::in);
	if (fileStream.is_open())
	{
		std::string line = "";

		while (getline(fileStream, line))
			shaderCode += "\n" + line;

		fileStream.close();
	}
	else
	{
		std::cout << "Cannot open file: " << filePath << std::endl;
		return -1;
	}

	GLint result = GL_FALSE;
	int infoLogLen;

	std::cout << "Compiling Shader: " << filePath << std::endl;
	char const* shaderSource = shaderCode.c_str();
	glShaderSource(shaderID, 1, &shaderSource, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLen);

	if (infoLogLen > 0)
	{
		std::vector<char> shaderError(infoLogLen + 1);
		glGetShaderInfoLog(shaderID, infoLogLen, NULL, &shaderError[0]);
		printf("%s\n", &shaderError[0]);
	}

	std::cout << "Shader compiled successfully!" << std::endl;
} 

//This links the OGL shader program. Takes in the program ID as a parameter.
GLint linkShaders(GLuint programID)
{
	GLint result = GL_FALSE;
	int infoLogLen;

	std::cout << "Linking Shaders!" << std::endl;

	if (programID == NULL)
		return -1;

	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLen);

	if (infoLogLen > 0)
	{
		std::vector<char> programError(infoLogLen + 1);
		glGetShaderInfoLog(programID, infoLogLen, NULL, &programError[0]);
		printf("%s\n", &programError[0]);
	}

	std::cout << "Shaders linked successfully!" << std::endl;
	std::cout << "----------------------------" << std::endl;
}

//Main shader loading method. Makes use of compileShader and linkShader functions. Takes in 3 file path parameters as char pointers
GLvoid Shader::loadComplieShaders(const char* vertex_path, const char* fragment_path, const char* geometry_path)
{
	GLuint programID, vertexID, fragmentID, geometryID;

	programID = glCreateProgram();

	if (vertex_path != NULL)
	{
		vertexID = glCreateShader(GL_VERTEX_SHADER);
		compileShader(vertex_path, vertexID);
		glAttachShader(programID, vertexID);
	}

	if (fragment_path != NULL)
	{
		fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
		compileShader(fragment_path, fragmentID);
		glAttachShader(programID, fragmentID);
	}

	if (geometry_path != NULL)
	{
		geometryID = glCreateShader(GL_GEOMETRY_SHADER);
		compileShader(geometry_path, geometryID);
		glAttachShader(programID, geometryID); 
	}

	linkShaders(programID);

	if (vertex_path != NULL)
	{ 
		glDetachShader(programID, vertexID);
		glDeleteShader(vertexID);
	}
	
	if (fragment_path != NULL)
	{
		glDetachShader(programID, fragmentID);
		glDeleteShader(fragmentID);
	}
	
	if (geometry_path != NULL)
	{
		glDetachShader(programID, geometryID);
		glDeleteShader(geometryID);
	}
	
	classProgramID = programID; 
}

#pragma region setUniform
#pragma region int
void Shader::setUniformInteger(const GLchar * name, GLint val)
{
	glUniform1i(glGetUniformLocation(getClassProgramID(), name), val);
}

void Shader::setUniformInteger(const GLchar * name, glm::vec2 val)
{
	glUniform2i(glGetUniformLocation(getClassProgramID(), name), val.x, val.y);
}

void Shader::setUniformInteger(const GLchar * name, glm::vec3 val)
{
	glUniform3i(glGetUniformLocation(getClassProgramID(), name), val.x, val.y, val.z);
}

void Shader::setUniformInteger(const GLchar * name, glm::vec4 val)
{
	glUniform4i(glGetUniformLocation(getClassProgramID(), name), val.x, val.y, val.z, val.w);
}
#pragma endregion

#pragma region matrices
void Shader::setUniformMatrix2(const GLchar * name, const GLfloat * val, GLboolean transpose)
{
	glUniformMatrix2fv(glGetUniformLocation(getClassProgramID(), name), 1, transpose, val);
}
void Shader::setUniformMatrix3(const GLchar * name, const GLfloat * val, GLboolean transpose)
{
	glUniformMatrix3fv(glGetUniformLocation(getClassProgramID(), name), 1, transpose, val);
}
void Shader::setUniformMatrix4(const GLchar * name, const GLfloat * val, GLboolean transpose)
{
	glUniformMatrix4fv(glGetUniformLocation(getClassProgramID(), name), 1, transpose, val);
}
#pragma endregion

#pragma region float
void Shader::setUniformFloat(const GLchar * name, GLfloat val)
{
	glUniform1f(glGetUniformLocation(getClassProgramID(), name), val);
}

void Shader::setUniformFloat(const GLchar * name, glm::vec2 val)
{
	glUniform2f(glGetUniformLocation(getClassProgramID(), name), val.x, val.y);
}

void Shader::setUniformFloat(const GLchar * name, glm::vec3 val)
{
	glUniform3f(glGetUniformLocation(getClassProgramID(), name), val.x, val.y, val.z);
}
void Shader::setUniformFloat(const GLchar * name, glm::vec4 val)
{
	glUniform4f(glGetUniformLocation(getClassProgramID(), name), val.x, val.y, val.z, val.w);
}
#pragma endregion
#pragma endregion

