#ifndef SHADER_H
#define SHADER_H

#include <gl/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader {
private:
	GLuint vertex;
	GLuint geometry;
	GLuint fragment;
	GLuint shaderProgram;
	GLuint loadShader(GLint type, std::string filename) {
		// loading shader from file
		std::string code;
		std::ifstream shaderFile;
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			shaderFile.open(filename);
			std::stringstream shaderFileStream;
			shaderFileStream << shaderFile.rdbuf();
			shaderFile.close();
			code = shaderFileStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "Error: couldn't load shader file " << filename << std::endl;
		}

		// compile shader
		const char * shaderCode = code.c_str();
		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &shaderCode, NULL);
		glCompileShader(shader);

		// error handling
		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "Error: couldn't compile " << type << " shader\n" << infoLog << std::endl;
		};

		return shader;
	}
public:
	Shader(std::string vertexFile, std::string geometryFile, std::string fragmentFile) {
		// load files
		vertex = loadShader(GL_VERTEX_SHADER, vertexFile);
		geometry = (geometryFile.empty()) ? (0) : (loadShader(GL_GEOMETRY_SHADER, geometryFile));
		fragment = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

		// create shader program
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertex);
		if (geometryFile.empty()) glAttachShader(shaderProgram, geometry);
		glAttachShader(shaderProgram, fragment);
		glLinkProgram(shaderProgram);

		// error handling
		int success;
		char infoLog[512];
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "Error: couldn't link shader program\n" << infoLog << std::endl;
		}
	}
	~Shader() {
		glDetachShader(shaderProgram, vertex);
		if (geometry != NULL) glDetachShader(shaderProgram, geometry);
		glDetachShader(shaderProgram, fragment);

		glDeleteShader(vertex);
		if (geometry != NULL) glDeleteShader(geometry);
		glDeleteShader(fragment);

		glDeleteProgram(shaderProgram);
	}
	void use() {
		glUseProgram(shaderProgram);
	}
	GLuint getUniformLocation(std::string variable) {
		return glGetUniformLocation(shaderProgram, variable.c_str());
	}
	GLuint getAttribLocation(std::string variable) {
		return glGetAttribLocation(shaderProgram, variable.c_str());
	}
	//----------------------------------------------------------------------------------------
	void setAttrVec2(const std::string &name, GLuint vbo) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		GLuint buf_id = glGetAttribLocation(shaderProgram, name.c_str());
		glEnableVertexAttribArray(buf_id);
		glVertexAttribPointer(buf_id, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	}
	void setAttrVec3(const std::string &name, GLuint vbo) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		GLuint buf_id = glGetAttribLocation(shaderProgram, name.c_str());
		glEnableVertexAttribArray(buf_id);
		glVertexAttribPointer(buf_id, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}
	void setAttrVec4(const std::string &name, GLuint vbo) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		GLuint buf_id = glGetAttribLocation(shaderProgram, name.c_str());
		glEnableVertexAttribArray(buf_id);
		glVertexAttribPointer(buf_id, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	}
	//----------------------------------------------------------------------------------------
	void setUnifVec2(const std::string &name, const glm::vec2 &value) const
	{
		glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
	}
	void setUnifVec3(const std::string &name, const glm::vec3 &value) const
	{
		glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
	}
	void setUnifVec4(const std::string &name, const glm::vec4 &value) const
	{
		glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
	}
	void setUnifMat2(const std::string &name, const glm::mat2 &mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void setUnifMat3(const std::string &name, const glm::mat3 &mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void setUnifMat4(const std::string &name, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
};

#endif