#include "GLIMCubes.h"
#include "../lodepng/lodepng.h"
#include <assert.h>
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
GLIMCubes::GLIMCubes(void) : vertex_buffer(0), instance_buffer(0){
	
}
GLIMCubes::~GLIMCubes(){

	GLuint disposeBuffers[2];
	disposeBuffers[0] = instance_buffer;
	disposeBuffers[1] = vertex_buffer;
	glDeleteBuffers(2, disposeBuffers);
}
void GLIMCubes::init(){

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	shaderHnd = initShaders("shaders/cube_vs.glsl", "shaders/cube_fs.glsl");
	static const GLfloat unitSize = 1.0f;
	static const GLfloat vertex_buffer_data[] = {
		-unitSize, -unitSize,	-unitSize, 1.0f, 0.0f,
		unitSize, -unitSize,	-unitSize, 0.0f, 1.0f,
		unitSize, unitSize,		-unitSize, 0.0f, 1.0f,
		-unitSize,  unitSize,	-unitSize, 1.0f, 0.0f,

		-unitSize, -unitSize,	unitSize, 1.0f, 0.0f,
		unitSize, -unitSize,	unitSize, 0.0f, 1.0f,
		unitSize, unitSize,		unitSize, 0.0f, 1.0f,
		-unitSize,  unitSize,	unitSize, 1.0f, 0.0f,


	};
	// create base vertex buffer
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	// create instance buffer
	/*glGenBuffers(1, &instance_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, instance_buffer);
	glBufferData(GL_ARRAY_BUFFER, primitiveDesc.allocatedSize() * sizeof(IMPrimitiveDesc), nullptr, GL_STREAM_DRAW);*/
}
void GLIMCubes::drawLine(Vector2 pos0, Vector2 pos1){
	IMPrimitiveDesc newDesc;
	newDesc.from_pos.x = pos0.x;
	newDesc.from_pos.y = pos0.y;


	newDesc.to_pos.x = pos1.x;
	newDesc.to_pos.y = pos1.y;

	primitiveDesc.push(newDesc);
}
void GLIMCubes::updateBuffer() {
	if (instance_buffer == 0) {
		glGenBuffers(1, &instance_buffer);
	}
	glBindBuffer(GL_ARRAY_BUFFER, instance_buffer);
	glBufferData(GL_ARRAY_BUFFER, primitiveDesc.allocatedSize() * sizeof(IMPrimitiveDesc), NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, primitiveDesc.allocatedSize() * sizeof(IMPrimitiveDesc), primitiveDesc.getPtr());
	//glUnmapBuffer(instance_buffer);
	//primitiveDesc.clear();
	
}
void GLIMCubes::onRender(glm::mat4 proj_view_mat){
	GLuint err;
	// shader switch
	glUseProgram(shaderHnd);
	//glEnable(GL_CULL_FACE);
	glUniformMatrix4fv(viewprojMatrixHnd, 1, GL_FALSE, &proj_view_mat[0][0]);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(GLfloat) * 5,                  // stride
		BUFFER_OFFSET(0)
		);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1, 
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(GLfloat) * 5,                  // stride
		BUFFER_OFFSET(sizeof(GL_FLOAT) * 3)
		);
	// instance buffer
	glBindBuffer(GL_ARRAY_BUFFER, instance_buffer);
	err = glGetError();
	glEnableVertexAttribArray(2);
	err = glGetError();
	glVertexAttribPointer(
		2, 
		3,
		GL_FLOAT, 
		GL_FALSE, 
		sizeof(IMPrimitiveDesc),
		BUFFER_OFFSET(0)
		);
	// rotation
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(
		3,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(IMPrimitiveDesc),
		BUFFER_OFFSET(sizeof(GLfloat) * 3)
		);
	// scale
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(
		4, 
		1, 
		GL_FLOAT,
		GL_FALSE,
		sizeof(IMPrimitiveDesc),
		BUFFER_OFFSET(sizeof(GLfloat) * 6)
		);
	// instance uv
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(
		5,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(IMPrimitiveDesc),
		BUFFER_OFFSET(sizeof(GLfloat) * 7)
		);
	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 0);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	err = glGetError();
	glDrawArraysInstanced(GL_LINES, 0, 8, primitiveDesc.length);
	err = glGetError();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	err = glGetError();
	primitiveDesc.clear();
}
GLuint GLIMCubes::initShaders(const char* vertex_file_path, const char* fragment_file_path) {
	CharBuffer* vshaderCode = CharHelper::loadTextFile(vertex_file_path);
	CharBuffer* fshaderCode = CharHelper::loadTextFile(fragment_file_path);
	// Create the shaders
	GLuint vshaderHnd = glCreateShader(GL_VERTEX_SHADER);
	GLuint fshaderHnd = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Fragment Shader code from the file
	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling vshader : %s\n", vertex_file_path);
	glShaderSource(vshaderHnd, 1, &vshaderCode->buffer, NULL);
	glCompileShader(vshaderHnd);

	// Check Vertex Shader
	glGetShaderiv(vshaderHnd, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vshaderHnd, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		char msg[255];
		//glGetShaderInfoLog(vshaderHnd, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		glGetShaderInfoLog(vshaderHnd, InfoLogLength, NULL, msg);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}


	// Compile Fragment Shader
	printf("Compiling fshader : %s\n", fragment_file_path);
	glShaderSource(fshaderHnd, 1, &fshaderCode->buffer, NULL);
	glCompileShader(fshaderHnd);

	// Check Fragment Shader
	glGetShaderiv(fshaderHnd, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fshaderHnd, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(fshaderHnd, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vshaderHnd);
	glAttachShader(ProgramID, fshaderHnd);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	
	glDetachShader(ProgramID, vshaderHnd);
	glDetachShader(ProgramID, fshaderHnd);

	glDeleteShader(vshaderHnd);
	glDeleteShader(fshaderHnd);
	vshaderCode->dispose();
	fshaderCode->dispose();

	viewprojMatrixHnd = glGetUniformLocation(ProgramID, "mat_view_proj");
	//GLuint err = glGetError();
	return ProgramID;
}