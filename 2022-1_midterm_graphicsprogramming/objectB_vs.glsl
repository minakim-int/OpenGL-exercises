#version 430 core													
layout (location = 0) in vec3 pos;    
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

uniform mat4 rotMat;										

out vec3 vs_color;						 							
out vec2 vsTexCoord;

void main(void)													
{																	
	gl_Position = rotMat*vec4(pos.x, pos.y, pos.z, 1.0);						
	vs_color = color;
	vsTexCoord = texCoord;
}																	