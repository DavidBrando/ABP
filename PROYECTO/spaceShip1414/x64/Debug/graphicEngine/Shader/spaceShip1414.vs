#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture;
layout (location = 2) in vec3 normal;

uniform mat4 mvp_matrix;
uniform mat4 mv_matrix;
uniform mat3 n_matrix;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main(void)
{
	Normal = n_matrix * normal;
	TexCoords = texture;
	FragPos = (mv_matrix * vec4(position, 1.0)).xyz;

	gl_Position = mvp_matrix * vec4(position, 1.0);
}
