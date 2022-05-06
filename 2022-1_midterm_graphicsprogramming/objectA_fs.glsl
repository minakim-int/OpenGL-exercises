#version 430 core

in vec3 vsColor;	
in vec2 vsTexCoord;
in vec3 vspos;

uniform sampler2D t1;

out vec4 fragColor;					
									
void main(void)						
{										
		fragColor = texture(t1, vsTexCoord);
	
}                    