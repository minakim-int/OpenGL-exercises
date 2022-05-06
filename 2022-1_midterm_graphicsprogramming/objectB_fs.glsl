#version 430 core                          
                                           
in vec3 vs_color;	
in vec2 vsTexCoord;

uniform sampler2D texture1;

out vec4 fragColor;                            
                                           
void main(void)                            
{                                          
    fragColor = vec4(vs_color, 1.0) * texture(texture1, vsTexCoord);

}                                          