
#version 330 core

// Fragment Shader Input
in vec3 ourFragPos;
in vec3 ourColor;
in vec3 ourNormal;

// Texture samplers
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 emissive;
uniform vec3 viewPos;
uniform vec3 shotPositions[10];
uniform vec3 paintColors[10];
//uniform sampler2D gridTexture;

// Fragment Shader Outputs
out vec4 color;

void main() {
	vec3 norm = normalize(ourNormal);
	vec3 lightDir = normalize(lightPos - ourFragPos);
	vec3 result;
	
	// === AMBIENT ===
	float ambientStrength = 0.2f;
    vec3 ambient = ambientStrength * lightColor;
	
	// === DIFFUSE ===
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;
	
	result = (ambient + diffuse) * ourColor;
	
	for (int i = 0; i < 10; i++) {
		vec3 distanceToShot = shotPositions[i] - ourFragPos;
		float magnitude = length(distanceToShot);

		// Make int as a uniform for blob size
		if (magnitude < 1) {
			if (result.x <= 0.5f) {
				result.x = 0.5f;
			}
			result = diff * (emissive + paintColors[i]);
		}
	}
	
	color = vec4(result, 1.0f);
}