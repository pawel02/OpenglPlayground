#version 420
layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

// Cannot use the shadred projection since we have to get rid off the translation on the view
uniform mat4 viewProjection;

void main()
{
	TexCoords = aPos;
	vec4 pos = viewProjection * vec4(aPos, 1.0);
	gl_Position = pos.xyww;
}