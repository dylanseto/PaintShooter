
#version 330 core

// Fragment Shader Input
in vec3 ourFragPos;
flat in vec3 ourColor;
flat in vec3 ourNormal;
//in vec2 outTexCoord;
//in float outTextureOpacity;

// Texture samplers
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 paintColor;
uniform vec3 shootPosition;
uniform vec3 emissive;
uniform vec3 viewPos;
//uniform sampler2D gridTexture;

// Fragment Shader Outputs
out vec4 color;

void main() {
	vec3 norm = normalize(ourNormal);
	vec3 lightDir = normalize(lightPos - ourFragPos);
	vec3 viewDir = normalize(viewPos - ourFragPos);
	vec3 result;
	
	// === SPECULAR ===
	vec3 reflectDir = reflect(-lightDir, norm);
	float shininess = 60.0f;
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), shininess);
	vec3 specular = lightColor * spec;
	if (ourFragPos.y <= 0.02f) {
	    specular = vec3(0.0f, 0.0f, 0.0f);
	}
	
	// === AMBIENT ===
	float ambientStrength = 0.2f;
    vec3 ambient = ambientStrength * lightColor;
	
	// === DIFFUSE ===
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;
	
	result = (ambient + diffuse) * ourColor;
	
	vec3 distanceToShot = shootPosition - ourFragPos;
	float mag = length(distanceToShot);
	
	// Make int as a uniform for blob size
	if (mag < 1) {
	    if (result.x <= 0.5f) {
		    result.x = 0.5f;
		}
	    result *= emissive + paintColor;
	}
	
	color = vec4(result, 1.0f);
}