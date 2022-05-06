#include <sb7.h>
#include <vmath.h>
#include <shader.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class textures {
public:
	GLuint texture;
	int width, height, nrChannels;
	unsigned char* data;
	void load(char* path) {
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		data = stbi_load(path, &width, &height, &nrChannels, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		stbi_image_free(data); 

	}
};
class my_application : public sb7::application
{
public:
	GLuint compile_shaders_objectA(void)
	{
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		vertex_shader = sb7::shader::load("objectA_vs.glsl", GL_VERTEX_SHADER);
		fragment_shader = sb7::shader::load("objectA_fs.glsl", GL_FRAGMENT_SHADER); 
		
		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		
		return program;
	}

	GLuint compile_shaders_objectB(void) {
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		vertex_shader = sb7::shader::load("objectB_vs.glsl", GL_VERTEX_SHADER);
		fragment_shader = sb7::shader::load("objectB_fs.glsl", GL_FRAGMENT_SHADER);

		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;
	}

	virtual void startup()
	{
		rendering_program_objectA = compile_shaders_objectA();
		rendering_program_objectB = compile_shaders_objectB();
		
		textureA.load((char*)"textures/wall.jpg");
		
		t1.load((char*)"textures/side1.png");
		t2.load((char*)"textures/side2.png");
		t3.load((char*)"textures/side3.png");
		t4.load((char*)"textures/side4.png");
		t5.load((char*)"textures/side5.png");
		t6.load((char*)"textures/side6.png");

		SettingVnB();
		
	}
	void SettingVnB() {
		GLfloat verticesB[] = {
			1.f, -1.f, 1.0f, 1.0f, 0.0f, 0.0f, 2.0f, 2.0f, //up-right
			1.f, -1.f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, //up-left
			-1.f, -1.f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //down-left
			-1.f, -1.f, 1.0f, 1.0f, 1.0f, 0.0f, 2.0f, 0.0f //down-right
		};
		GLuint indicesB[] = {
			0, 1, 2,
			0, 2, 3
		};
		GLfloat verticesA[] = { 
			-0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, //up-left
			0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //down-right
			-0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //down-left

			0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //down-right
			-0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, //up-left
			0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, //up-right
			////////////////////////////////////////
			0.25f, -0.25f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, //down-left
			0.25f, 0.25f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //up-left
			0.25f, -0.25f, 0.25f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //down-right

			0.25f, -0.25f, 0.25f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //down-right
			0.25f, 0.25f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //up-left
			0.25f, 0.25f, 0.25f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, //up-right
			///////////////////////////////////////
			0.25f, -0.25f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //down-left
			0.25f, 0.25f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //up-left
			-0.25f, -0.25f, 0.25f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, //down-right

			-0.25f, -0.25f, 0.25f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, //down-right
			0.25f, 0.25f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //up-left
			-0.25f, 0.25f, 0.25f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, //up-right
			///////////////////////////////////////
			-0.25f, -0.25f, 0.25f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, //down-left
			-0.25f, 0.25f, 0.25f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, //up-left
			-0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, //down-right

			-0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, //down-right
			-0.25f, 0.25f, 0.25f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, //up-left
			-0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, //up-right
			////////////////////////////////////////
			-0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, //down-left
			0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, //up-right
			0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //down-right

			0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, //up-right
			-0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, //down-left
			-0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, //up-left
			////////////////////////////////////////
			-0.25f, 0.25f, -0.25f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, //down-left
			0.25f, 0.25f, 0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, //up-right
			0.25f, 0.25f, -0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, //down-right

			0.25f, 0.25f, 0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, //up-right
			-0.25f, 0.25f, -0.25f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, //down-left
			-0.25f, 0.25f, 0.25f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f //up-left
		};
		/////////////////Generating VAO&Buffers////////////////////
		glGenVertexArrays(2, VAO);
		glGenBuffers(2, VBO); 
		glGenBuffers(1, &EBO);

		//////////////////Binding VAO &Buffers/////////////////////////////////
		// first VAO
		glBindVertexArray(VAO[0]);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesB), verticesB, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesB), indicesB, GL_STATIC_DRAW);

		// coordinate position (location = 0)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color (location = 1)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture position (location = 2)
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		/////////////////////////////////////////////////////////////////////////////////
		// second VAO
		glBindVertexArray(VAO[1]);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesA), verticesA, GL_STATIC_DRAW);

		// coordinate position (location = 0)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color (location = 1)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture position (location = 2)
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

	}

	virtual void shutdown()
	{
		glDeleteVertexArrays(2, VAO);
		glDeleteProgram(rendering_program_objectA);
		glDeleteProgram(rendering_program_objectB);
	}

	virtual void render(double currentTime)
	{
		const GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
		glClearBufferfv(GL_COLOR, 0, black);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		float angle = currentTime * 150;
		vmath::mat4 tm = vmath::translate(vmath::vec3((float)sin(currentTime), 0.0f, (float)cos(currentTime) * 0.3f));
		vmath::mat4 rm = vmath::rotate(angle, 0.0f, 0.0f, -1.0f);
		vmath::mat4 rm3 = vmath::rotate(angle, 0.0f, -1.0f, 0.0f);
														
		vmath::vec3 eye((float)currentTime * 0.1, 1.0, -1.0);
		vmath::vec3 target(0.0, 0.0, 0.0);
		vmath::vec3 up(0.0, 0.2, 0.0);
		vmath::mat4 vm = vmath::lookat(eye, target, up);
		vmath::mat4 pm = vmath::perspective(50.f, info.windowWidth / (float)info.windowHeight, 0.1f, 1000.0f);
		
		glUseProgram(rendering_program_objectA);
		glUniform1i(glGetUniformLocation(rendering_program_objectA, "t1"), 1);
		glActiveTexture(GL_TEXTURE1); 
		glBindTexture(GL_TEXTURE_2D, t1.texture);

		glUniform1i(glGetUniformLocation(rendering_program_objectA, "t1"), 2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, t2.texture);

		glUniform1i(glGetUniformLocation(rendering_program_objectA, "t1"), 3);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, t3.texture);

		glUniform1i(glGetUniformLocation(rendering_program_objectA, "t1"), 4);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, t4.texture);

		glUniform1i(glGetUniformLocation(rendering_program_objectA, "t1"), 5);
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, t5.texture);

		glUniform1i(glGetUniformLocation(rendering_program_objectA, "t1"), 6);
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, t6.texture);
	
		
		GLint rotMatLocation = glGetUniformLocation(rendering_program_objectA, "rotMat");
		// cube rotation matrix
		glUniformMatrix4fv(rotMatLocation, 1, GL_FALSE, pm * vm * rm3 * rm);

		//Draw cube
		glBindVertexArray(VAO[1]);
		glEnable(GL_CULL_FACE);
		glBindTexture(GL_TEXTURE_2D, t1.texture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindTexture(GL_TEXTURE_2D, t2.texture);
		glDrawArrays(GL_TRIANGLES, 6, 8);
		glBindTexture(GL_TEXTURE_2D, t3.texture);
		glDrawArrays(GL_TRIANGLES, 9, 11);
		glBindTexture(GL_TEXTURE_2D, t4.texture);
		glDrawArrays(GL_TRIANGLES, 12, 14); 
		glBindTexture(GL_TEXTURE_2D, t5.texture);
		glDrawArrays(GL_TRIANGLES, 15, 17);
		glBindTexture(GL_TEXTURE_2D, t6.texture);
		glDrawArrays(GL_TRIANGLES, 24, 36);
										 
		///////////////////////////////////////////////////////////////////////////
	
		glUseProgram(rendering_program_objectB);
		GLint rotMatLocation2 = glGetUniformLocation(rendering_program_objectB, "rotMat");
		// vmath::mat4 size = vmath::mat4(2.0, 0.0, 0.0, 2.0);
		vmath::mat4 pm2 = vmath::perspective(50.f, info.windowWidth / (float)info.windowHeight, 0.1f, 1000.0f);

		glUniformMatrix4fv(rotMatLocation2, 1, GL_FALSE, pm * vm);
		glUniform1i(glGetUniformLocation(rendering_program_objectB, "texture1"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureA.texture);

		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	}
private:
	GLuint rendering_program_objectA, rendering_program_objectB, rendering_program_stick;
	GLuint VAO[2], VBO[2], EBO;
	textures textureA, t1, t2, t3, t4, t5, t6;
};

DECLARE_MAIN(my_application)
