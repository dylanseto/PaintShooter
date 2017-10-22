
#version 330 core


// Fragment Shader Input
in vec3 ourColor;
in vec2 outTexCoord;

// Texture samplers
uniform sampler2D gridTexture;

// Fragment Shader Outputs
out vec4 color;


void main() {
	color = texture(gridTexture, outTexCoord) * vec4(ourColor, 1.0f);
}


