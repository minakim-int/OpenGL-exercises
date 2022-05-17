#pragma once
#include <sb7.h>
#include <shader.h>
#include <vmath.h>

class Shader {
private:
	GLuint program;

public:
	GLuint getProgID() const {
		return program;
	}
	void load(const GLchar *v_path, const char *f_path) {
		const GLuint vs_file = sb7::shader::load(v_path, GL_VERTEX_SHADER);
		const GLuint fs_file = sb7::shader::load(f_path, GL_FRAGMENT_SHADER);
		
		program = glCreateProgram();
		glAttachShader(program, vs_file);
		glAttachShader(program, fs_file);
		glLinkProgram(program);

		glDeleteShader(vs_file);
		glDeleteShader(fs_file);
	}
	void use() const 
	{
		glUseProgram(program);
	}
	void setVec3(const GLchar *u_name, vmath::vec3& v3_name) const 
	{
		glUniform3fv(glGetUniformLocation(program, u_name), 1, v3_name);
	}
	void setFloat(const GLchar *u_name, float& f_name) const 
	{
		glUniform1f(glGetUniformLocation(program, u_name), f_name);
	}
	void setFloat2(const GLchar* u_name, float& f_name1, float& f_name2) {
		glUniform2f(glGetUniformLocation(program, u_name), f_name1, f_name2);
	}
	void setFloat2(const GLchar* u_name, vmath::vec2 f_name) {
		glUniform2f(glGetUniformLocation(program, u_name), f_name[0], f_name[1]);
	}
	void setMat4(const GLchar *u_name, vmath::mat4& m4_name) const
	{
		// GLint location, GLsizei count, GLboolean transpose, const GLfloat *value
		glUniformMatrix4fv(glGetUniformLocation(program, u_name), 1, GL_FALSE, m4_name);
	}
	void setInt(const GLchar *u_name, GLint& i_name) const 
	{
		glUniform1i(glGetUniformLocation(program, u_name), i_name);
	}
	~Shader() 
	{
		glDeleteProgram(program);
	}
};

