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
struct IMLineDesc {
	Vector3 from_pos;
	Vector4 color;
	IMLineDesc() {
	}
};

class GLIMLines{
private:
	GLuint vertex_buffer; // base vertex buffer
	
	ArrayStruct<IMLineDesc> primitiveDesc;
	ArrayStruct<IMLineDesc> tmpPrimitiveDesc;
	int sprite_max;
	GLuint viewprojMatrixHnd;
	GLuint shaderHnd;
	GLuint initShaders(const char* vertex_file_path, const char* fragment_file_path);
public:
	GLIMLines(void);
	~GLIMLines();
	// overrides
	void init(void);
	void onRender(glm::mat4 proj_view_mat);
	void drawLine(Vector2 pos0, Vector2 pos1, Color color);
	
	void updateBuffer(void);
	
};
