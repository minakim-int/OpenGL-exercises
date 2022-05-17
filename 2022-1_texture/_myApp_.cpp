#include <sb7.h>
#include <vmath.h>
#include <string>
#include "glfw3.h"
#include "Shader.h"
#include "Texture.h"

class my_application : public sb7::application
{
private:
	Shader shader_box, shader_floor;
	GLuint VAOs[2], VBOs[2], EBOs[1];
	Textures textures[6], wall, container;
public:
	virtual void startup()
	{
		shader_box.load("texture_vs.glsl", "texture_fs.glsl");
		shader_floor.load("texture_color_vs.glsl", "texture_color_fs.glsl");

		glGenVertexArrays(2, VAOs);
		glGenBuffers(2, VBOs);
		glGenBuffers(1, EBOs);
		
		for (int i = 0; i < sizeof(textures)/sizeof(textures[0]); i++) {
			textures[i].genTextures();
		}
		glBindVertexArray(VAOs[0]);
		float floor_s = 3.0f, floor_t = 3.0f;
		GLfloat floor_vertices[] = {
			1.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, floor_s, floor_t,  // 우측 상단
			-1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, floor_t,  // 좌측 상단
			-1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // 좌측 하단
			1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, floor_s, 0.0f   // 우측 하단
		};

		GLuint floor_indices[] = {
			0, 1, 2,	// 첫번째 삼각형
			0, 2, 3		// 두번째 삼각형
		};

		glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(floor_vertices), floor_vertices, GL_STATIC_DRAW);

		// (location = 0)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// (location = 1)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// (location = 2)
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(floor_indices), floor_indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


		glBindVertexArray(VAOs[1]);
		float box_s = 1.0f, box_t = 1.0f;
		GLfloat box_vertices[] = {
			// 뒷면
			-0.25f, 0.5f, -0.25f, 1.0f, 0.0f, 0.0f, box_s, box_t,
			0.25f, 0.0f, -0.25f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			-0.25f, 0.0f, -0.25f, 1.0f, 0.0f, 0.0f, box_s, 0.0f,

			0.25f, 0.0f, -0.25f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			-0.25f, 0.5f, -0.25f, 1.0f, 0.0f, 0.0f, box_s, box_t,
			0.25f, 0.5f, -0.25f, 1.0f, 0.0f, 0.0f, 0.0f, box_t,
			// 우측면
			0.25f, 0.0f, -0.25f, 0.0f, 1.0f, 0.0f, box_s, 0.0f,
			0.25f, 0.5f, -0.25f, 0.0f, 1.0f, 0.0f, box_s, box_t,
			0.25f, 0.0f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

			0.25f, 0.0f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			0.25f, 0.5f, -0.25f, 0.0f, 1.0f, 0.0f, box_s, box_t,
			0.25f, 0.5f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, box_t,
			// 정면
			0.25f, 0.0f, 0.25f, 0.0f, 0.0f, 1.0f, box_s, 0.0f,
			0.25f, 0.5f, 0.25f, 0.0f, 0.0f, 1.0f, box_s, box_t,
			-0.25f, 0.0f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

			-0.25f, 0.0f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.25f, 0.5f, 0.25f, 0.0f, 0.0f, 1.0f, box_s, box_t,
			-0.25f, 0.5f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, box_t,
			// 좌측면
			-0.25f, 0.0f, 0.25f, 1.0f, 0.0f, 1.0f, box_s, 0.0f,
			-0.25f, 0.5f, 0.25f, 1.0f, 0.0f, 1.0f, box_s, box_t,
			-0.25f, 0.0f, -0.25f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

			-0.25f, 0.0f, -0.25f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.25f, 0.5f, 0.25f, 1.0f, 0.0f, 1.0f, box_s, box_t,
			-0.25f, 0.5f, -0.25f, 1.0f, 0.0f, 1.0f, 0.0f, box_t,
			// 바닥면
			-0.25f, 0.0f, 0.25f, 1.0f, 1.0f, 0.0f, box_s, 0.0f,
			0.25f, 0.0f, -0.25f, 1.0f, 1.0f, 0.0f, 0.0f, box_t,
			0.25f, 0.0f, 0.25f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

			0.25f, 0.0f, -0.25f, 1.0f, 1.0f, 0.0f, 0.0f, box_t,
			-0.25f, 0.0f, 0.25f, 1.0f, 1.0f, 0.0f, box_s, 0.0,
			-0.25f, 0.0f, -0.25f, 1.0f, 1.0f, 0.0f, box_s, box_t,
			// 윗면
			-0.25f, 0.5f, -0.25f, 0.0f, 1.0f, 1.0f, 0.0f, box_t,
			0.25f, 0.5f, 0.25f, 0.0f, 1.0f, 1.0f, box_s, 0.0f,
			0.25f, 0.5f, -0.25f, 0.0f, 1.0f, 1.0f, box_s, box_t,

			0.25f, 0.5f, 0.25f, 0.0f, 1.0f, 1.0f, box_s, 0.0f,
			-0.25f, 0.5f, -0.25f, 0.0f, 1.0f, 1.0f, 0.0f, box_t,
			-0.25f, 0.5f, 0.25f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f
		};

		glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(box_vertices), box_vertices, GL_STATIC_DRAW);

		// (location = 0)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// (location = 1)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// (location = 2)
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

				
		// 텍스처 로드 --------------------------------------------------
		wall.load("textures/wall.jpg");
		container.load("textures/container.jpg");
		std::string path = "textures/side.png";
		int dot_loc = path.find('.');
		for (int i = 0; i < sizeof(textures)/sizeof(textures[0]); i++) {
			std::string path_copy = path;
			std::string path_num = path_copy.insert(dot_loc, std::to_string(i+1));
			textures[i].load(path_num);
		}
	}

	virtual void shutdown()
	{
		glDeleteBuffers(1, EBOs);
		glDeleteBuffers(2, VBOs);
		glDeleteVertexArrays(2, VAOs);
	}

	virtual void render(double currentTime)
	{
		const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f, (float)cos(currentTime) * 0.5f + 0.5f, 0.0f, 1.0f };
		const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, black);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		float distance = 2.f;
		vmath::vec3 eye((float)cos(currentTime * 0.1f) * distance, 0.7, (float)sin(currentTime * 0.1f) * distance);
		vmath::vec3 center(0.0, 0.0, 0.0);
		vmath::vec3 up(0.0, 1.0, 0.0);
		vmath::mat4 lookAt = vmath::lookat(eye, center, up);
		float fov = 50.f;// (float)cos(currentTime)*20.f + 50.0f;
		vmath::mat4 projM = vmath::perspective(fov, info.windowWidth / (float)info.windowHeight, 0.1f, 1000.0f);

		shader_floor.use();
		vmath::mat4 transformM = projM * lookAt * vmath::translate(0.f, -0.25f, 0.f) * vmath::scale(1.5f);
		shader_floor.setMat4("transform", transformM);
		wall.bind(shader_floor, "texture1", 0);
		glBindVertexArray(VAOs[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		vmath::mat4 transM = vmath::translate(0.0f,  0.5f, 0.0f);
		vmath::mat4 scaleM = vmath::scale((float)sin(currentTime) * 0.25f + 0.75f);
		float angle = currentTime * 100;
		vmath::mat4 rotateY = vmath::rotate(angle, 0.0f, 1.0f, 0.0f);
		vmath::mat4 rotateX = vmath::rotate(angle*0.5f, 1.0f, 0.0f, 0.0f);
		transformM = projM * lookAt * transM * rotateX * rotateY * vmath::translate(0.f, -0.25f, 0.f);
		shader_box.use();
		glBindVertexArray(VAOs[1]);
		shader_box.setMat4("transform", transformM);
		container.bind(shader_box, "container", 1);

		/* * * * * * * * * * * * *
		* FOR MOUSE INTERACTION
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		vmath::vec2 mousePos = vmath::vec2((float)xpos, (float)ypos);
		shader_box.setFloat2("mousePos", mousePos);
		*
		* * * * * * * * * * * * * */
		for (int i = 0; i < 6; i++)
		{
			textures[i].bind(shader_box, "texture1", 0);
			glDrawArrays(GL_TRIANGLES, 6*i, 6);
		}
	}
};

DECLARE_MAIN(my_application)