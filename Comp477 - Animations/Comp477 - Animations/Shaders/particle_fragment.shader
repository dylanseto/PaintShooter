
#version 330 core

// Fragment Shader Input
flat in vec3 ourColor;
in vec3 ourFragPos;
flat in vec3 ourNormal;

// Uniform Variables
uniform vec3 lightPos;
uniform vec3 lightColor;

// Fragment Shader Outputs
out vec4 color;

void main() {
    vec3 norm = normalize(ourNormal);
	vec3 lightDir = normalize(lightPos - ourFragPos);
	vec3 nightLight = vec3(0.490196f, 0.568627f, 0.670588f);
	vec3 light;
	vec3 result;

	// makes particles circular
	vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
	if (dot(circCoord, circCoord) > 1.0) {
		discard;
	}

	// === GLOW ===
	if (lightColor == nightLight) {
	    light = vec3(1.0f, 1.0f, 1.0f);
	}
	else {
	    light = lightColor;
	}
	
	// === AMBIENT ===
	float ambientStrength = 1.0f;
    vec3 ambient = ambientStrength * light;
	
	// === DIFFUSE ===
	float diff = max(dot(norm, lightDir), 0.1f);
	vec3 diffuse = diff * light;
	
	result = (ambient + diffuse) * ourColor;
	
	//Color
	color = vec4(result, 1.0f);
}


