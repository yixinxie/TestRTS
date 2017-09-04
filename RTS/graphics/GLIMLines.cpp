#include "GLIMLines.h"
#include "../lodepng/lodepng.h"
#include <assert.h>
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
GLIMLines::GLIMLines(void) : vertex_buffer(0), dirty(false){
	
}
GLIMLines::~GLIMLines(){

	GLuint disposeBuffers[1];
	disposeBuffers[0] = vertex_buffer;
	glDeleteBuffers(2, disposeBuffers);
}
void GLIMLines::init(){

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	shaderHnd = initShaders("shaders/line_vs.glsl", "shaders/line_fs.glsl");
}
void GLIMLines::drawLine(Vector2 pos0, Vector2 pos1, Color color){
	IMLineDesc newDesc;
	newDesc.pos.x = pos0.x;
	newDesc.pos.y = pos0.y;
	newDesc.color = color.toVec4();
	primitiveDesc.push(newDesc);

	newDesc.pos.x = pos1.x;
	newDesc.pos.y = pos1.y;
	newDesc.color = color.toVec4();
	primitiveDesc.push(newDesc);
}
void GLIMLines::updateBuffer() {
	//if (vertex_buffer == 0) {
	//	glGenBuffers(1, &vertex_buffer);
	//}
	//glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	//glBufferData(GL_ARRAY_BUFFER, primitiveDesc.allocatedSize() * sizeof(IMLineDesc), NULL, GL_STREAM_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, primitiveDesc.allocatedSize() * sizeof(IMLineDesc), primitiveDesc.getPtr());


	if (primitiveDesc.allocatedSize() != sprite_max) {

		if (sprite_max != 0) {
			GLuint singleBuffer[1];
			singleBuffer[0] = vertex_buffer;
			glDeleteBuffers(1, singleBuffer);
		}

		glGenBuffers(1, &vertex_buffer);
		sprite_max = primitiveDesc.allocatedSize();
	}
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sprite_max * sizeof(IMLineDesc), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, sprite_max * sizeof(IMLineDesc), primitiveDesc.getPtr());
	
	
}
void GLIMLines::onRender(glm::mat4 proj_view_mat){
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
		sizeof(IMLineDesc),                  // stride
		BUFFER_OFFSET(0)
		);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1, 
		4,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(IMLineDesc),                  // stride
		BUFFER_OFFSET(sizeof(GL_FLOAT) * 3)
		);
	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 0);
	err = glGetError();
	glDrawArrays(GL_LINES, 0, primitiveDesc.length);
	err = glGetError();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	err = glGetError();
	primitiveDesc.clear();
}
GLuint GLIMLines::initShaders(const char* vertex_file_path, const char* fragment_file_path) {
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