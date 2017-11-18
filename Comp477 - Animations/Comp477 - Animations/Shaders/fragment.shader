
#version 330 core


// Fragment Shader Input
in vec3 ourColor;
in vec2 outTexCoord;
in float outTextureOpacity;

// Texture samplers
uniform sampler2D gridTexture;

// Fragment Shader Outputs
out vec4 color;


void main() {
	color = mix(vec4(ourColor, 1.0f), texture(gridTexture, outTexCoord), outTextureOpacity) ;
}


