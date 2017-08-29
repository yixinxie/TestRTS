#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec2 sprite_pos;
layout(location = 3) in float sprite_rotation;
layout(location = 4) in vec2 sprite_scale;
layout(location = 5) in vec2 sprite_uv;
//in vec3 vertexPosition_modelspace;
//in vec2 vertexUV;

out vec2 UV;

// Values that stay constant for the whole mesh.
uniform mat4 mat_view_proj;

void main(){

	vec3 instance_pos = vec3(sprite_pos, 0);
	float cosine = cos(sprite_rotation);
	float sine = sin(sprite_rotation);
	vec2 offset = vec2(vertexPosition_modelspace.x * sprite_scale.x, vertexPosition_modelspace.y * sprite_scale.y);
	vec2 rotated = vec2(offset.x * cosine - offset.y * sine, offset.x * sine + offset.y * cosine);
	instance_pos.x += rotated.x;
	instance_pos.y += rotated.y;
	gl_Position = mat_view_proj * vec4(instance_pos,1);
	
	//UV = vertexUV / 12;
	UV = sprite_uv + vertexUV / 12;
}