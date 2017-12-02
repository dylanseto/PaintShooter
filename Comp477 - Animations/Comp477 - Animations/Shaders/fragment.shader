
#version 330 core

// Fragment Shader Input
in vec3 ourFragPos;
flat in vec3 ourColor;
flat in vec3 ourNormal;
in vec2 outTexCoord;
in float outTextureOpacity;

// Texture samplers
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform sampler2D gridTexture;

// Fragment Shader Outputs
out vec4 color;

void main() {
	vec3 norm = normalize(ourNormal);
	vec3 lightDir = normalize(lightPos - ourFragPos);
	vec3 objectColor = ourColor;
	vec3 result;
	
	// === AMBIENT ===
	float ambientStrength = 0.2f;
    vec3 ambient = ambientStrength * lightColor;
	
	// === DIFFUSE ===
	float diff = max(dot(norm, lightDir), 0.1f);
	vec3 diffuse = diff * lightColor;
	
	result = (ambient + diffuse) * objectColor;
	
	//if (outTextureOpacity < 1.0f) {
	//	color = vec4(result, 1.0f);
	//}
	//else {
	//	color = mix(vec4(ourColor, 1.0f), texture(gridTexture, outTexCoord), outTextureOpacity);
	//}
	color = mix(vec4(result, 1.0f), texture(gridTexture, outTexCoord), outTextureOpacity);
}