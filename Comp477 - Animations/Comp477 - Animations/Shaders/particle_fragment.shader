
#version 330 core


// Fragment Shader Input
in vec3 ourColor;

// Fragment Shader Outputs
out vec4 color;


void main() {

	// makes particles circular
	vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
	if (dot(circCoord, circCoord) > 1.0) {
		discard;
	}

	//Color
	color = vec4(ourColor, 1.0f);
}


