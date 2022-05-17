#version 430 core								
												
in vec3 vsColor;								
in vec2 vsTexCoord;							
uniform sampler2D texture1;	
uniform sampler2D container;
uniform vec2 mousePos;
												
out vec4 fragColor;							
												
void main(void)								
{												
	vec4 white = vec4(0.5, 0.5, 0.5, 1.0);
	vec4 tmpColor = texture(texture1, vsTexCoord);
	if(tmpColor.x > white.x && tmpColor.y > white.y && tmpColor.z > white.z )
	{
		fragColor = texture(container, vsTexCoord);
	}
	else
		//for mouse interaction
		//fragColor = vec4(normalize(mousePos), 1.0, 1.0);
		fragColor = texture(texture1, vsTexCoord);	
}												