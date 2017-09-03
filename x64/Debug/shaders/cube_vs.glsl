#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

layout(location = 2) in vec3 from_pos;
layout(location = 3) in vec3 to_pos;
layout(location = 4) in float thickness_scale;
layout(location = 5) in vec4 color;

//out vec2 UV;

// Values that stay constant for the whole mesh.
uniform mat4 mat_view_proj;

void main(){
	vec3 instance_pos = from_pos * vertexUV.x + to_pos * vertexUV.y + vertexPosition_modelspace;
	gl_Position = mat_view_proj * vec4(instance_pos, 1);
	
	//UV = sprite_uv + vertexUV / 12;
}