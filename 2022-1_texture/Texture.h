#include <string>
#include <sb7.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Textures {
private:
	int width, height, nrChannels;
	GLuint img;
	unsigned char* data;
public:
	void genTextures() {
		glGenTextures(1, &img);
	}
	void load(std::string path) {
		const char* path_cstr =	path.c_str();
		glGenTextures(1, &img);
		glBindTexture(GL_TEXTURE_2D, img);
		data = stbi_load(path_cstr, &width, &height, &nrChannels, 0);

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
	void bind(const Shader& prog_name, std::string texture_name, int num=0) const
	{
		const char* texture_name_cstr =	texture_name.c_str();
		glUniform1i(glGetUniformLocation(prog_name.getProgID(), texture_name_cstr), num);
		const int numbering = 0x84C0;
		glActiveTexture(numbering+num); // 0x84C0~DE
		glBindTexture(GL_TEXTURE_2D, img);
	}
	~Textures() {
		glDeleteTextures(1, &img);
	}
};
