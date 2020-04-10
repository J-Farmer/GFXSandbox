#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\glm\glm.hpp"
#include <vector>
class Shader
{
public:

	Shader() {};
	Shader(const char* vertex_path, const char* fragment_path, const char* geometry_path);

	GLvoid loadComplieShaders(const char* vertex_path, const char* fragment_path, const char* geometry_path); 

	GLvoid reloadShader() {  };

	inline GLuint getClassProgramID() { return classProgramID; };

	inline void useShader() { glUseProgram(getClassProgramID()); };
	inline void disableShader() { glUseProgram(0); }; 

	void setUniformInteger(const GLchar * name, GLint val);
	void setUniformInteger(const GLchar * name, glm::vec2 val);
	void setUniformInteger(const GLchar * name, glm::vec3 val);
	void setUniformInteger(const GLchar * name, glm::vec4 val);

	void setUniformMatrix2(const GLchar *name, const GLfloat *val, GLboolean transpose = GL_FALSE); //Matrix
	void setUniformMatrix3(const GLchar *name, const GLfloat *val, GLboolean transpose = GL_FALSE);
	void setUniformMatrix4(const GLchar *name, const GLfloat *val, GLboolean transpose = GL_FALSE); 

	void setUniformFloat(const GLchar *name, GLfloat val); //float values
	void setUniformFloat(const GLchar *name, glm::vec2 val);
	void setUniformFloat(const GLchar *name, glm::vec3 val); //vec3 values
	void setUniformFloat(const GLchar *name, glm::vec4 val);

private:
	GLuint classProgramID; 
	const char* vertex_path;
	const char* fragment_path;
	const char* geom_path; 
};

