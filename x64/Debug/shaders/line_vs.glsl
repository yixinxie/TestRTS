#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec4 vertex_color;

out vec4 vert_color;

// Values that stay constant for the whole mesh.
uniform mat4 mat_view_proj;

void main(){
	gl_Position = mat_view_proj * vec4(vertexPosition_modelspace, 1);
	vert_color = vertex_color;
}