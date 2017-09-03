// include the basic windows header files and the Direct3D header files
#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "../misc/SimpleVector.h"
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
#include "../misc/ArrayT.h"
using namespace OriGraphics;
struct IMPrimitiveDesc {
	Vector3 from_pos;
	Vector3 to_pos;
	float scale;
	Vector4 color;
	IMPrimitiveDesc() {
		//from_pos = Vector3::zero();
		//from_pos = Vector3::zero();
		//scale = 1.0f;
		//color.
	}
	//unsigned int states;
};

class GLIMCubes{
private:
	GLuint vertex_buffer; // base vertex buffer
	GLuint instance_buffer; // per instance data and states.
	ArrayStruct<IMPrimitiveDesc> primitiveDesc;
	ArrayStruct<IMPrimitiveDesc> tmpPrimitiveDesc;
	int sprite_count;
	int sprite_max;
	GLuint viewprojMatrixHnd;
	GLuint shaderHnd;
	GLuint initShaders(const char* vertex_file_path, const char* fragment_file_path);
public:
	GLIMCubes(void);
	~GLIMCubes();
	// overrides
	void init(void);
	void onRender(glm::mat4 proj_view_mat);
	void drawLine(Vector2 pos0, Vector2 pos1);
	
	void updateBuffer(void);
	
};
