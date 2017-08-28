#include "GLInstancedSprites.h"
#include "../lodepng/lodepng.h"
#include <assert.h>
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
GLInstancedSprites::GLInstancedSprites(void){
	
}
void GLInstancedSprites::dispose(){

	GLuint disposeBuffers[2];
	disposeBuffers[0] = instance_buffer;
	disposeBuffers[1] = vertex_buffer;
	glDeleteBuffers(2, disposeBuffers);

	deallocND(spriteDesc);
}
void GLInstancedSprites::init(){
	vertex_buffer = 0;
	instance_buffer = 0;

	sprite_count = 0;
	sprite_max = 4;
	spriteDesc = allocArray<SpriteDesc>(sprite_max, "init");

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	shaderHnd = initShaders("shaders/sprite_vs.glsl", "shaders/sprite_fs.glsl");

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f,	0.0f, 0.0,	0.0,
		1.0f, -1.0f,	0.0f, 1,	0,
		-1.0f,  1.0f,	0.0f, 0,	1,
		//-1.0f,  1.0f,	0.0f, 0,	1,
		//1.0f, -1.0f,	0.0f, 1,	0,
		1.0f, 1.0f,		0.0f, 1,	1,


	};
	// create base vertex buffer
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// create instance buffer
	glGenBuffers(1, &instance_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, instance_buffer);
	glBufferData(GL_ARRAY_BUFFER, sprite_max * sizeof(SpriteDesc), nullptr, GL_STREAM_DRAW);
}
GLuint GLInstancedSprites::newSpriteSheet(unsigned int width, unsigned int height, const char* spritePath){
	
	std::vector<unsigned char> pngData; //the raw pixels
	//unsigned int error = lodepng::load_file(pngData, "assets/arrows.png");
	unsigned int error = lodepng::load_file(pngData, spritePath);
	assert(error == 0);
	std::vector<unsigned char> image;
	unsigned char* imageBuffer;
	error = lodepng::decode(image, width, height, pngData);
	assert(error == 0);
	imageBuffer = image.data();
	// create texture in GPU.
	//resourceHandle = G::instance()->renderer->createTexture(width, height, imageBuffer);
	//assert(resourceHandle >= 0);
	textureId = createTexture(width, height, image.data());
	return textureId;

}
int GLInstancedSprites::newSprite(const Vector2 pos, const Vector2 uv) {
	GLuint er;
	int cur = sprite_count;
	sprite_count++;
	if (cur >= sprite_max) {
		
		GLuint singleBuffer[1];
		singleBuffer[0] = instance_buffer;
		glDeleteBuffers(1, singleBuffer);
		SpriteDesc* oldptr = spriteDesc;
		

		sprite_max *= 2;
		spriteDesc = allocArray<SpriteDesc>(sprite_max, "sprite desc");
		memcpy(spriteDesc, oldptr, sprite_max / 2 * sizeof(SpriteDesc));
		deallocND(oldptr);
		glGenBuffers(1, &instance_buffer);

		//glBindBuffer(GL_ARRAY_BUFFER, instance_buffer);
		//glBufferData(GL_ARRAY_BUFFER, sprite_max * sizeof(SpriteDesc), spriteDesc, GL_STREAM_DRAW);

	}
	const float unitUV = 1.0f / 12.0f;
	spriteDesc[cur].pos = pos;
	spriteDesc[cur].rotation_scale = Vector2(0, 1);
	spriteDesc[cur].uv.x = uv.x * unitUV;
	spriteDesc[cur].uv.y = uv.y * unitUV;
	glBindBuffer(GL_ARRAY_BUFFER, instance_buffer);
	glBufferData(GL_ARRAY_BUFFER, sprite_max * sizeof(SpriteDesc), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, sprite_max * sizeof(SpriteDesc), spriteDesc);
	return cur;
}
void GLInstancedSprites::updateSprite(int spriteId, const Vector2 pos) {
	spriteDesc[spriteId].pos = pos;
}
void GLInstancedSprites::updateBufferFromSpriteDesc() {
	glBindBuffer(GL_ARRAY_BUFFER, instance_buffer);
	glBufferData(GL_ARRAY_BUFFER, sprite_max * sizeof(SpriteDesc), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, sprite_max * sizeof(SpriteDesc), spriteDesc);
}
void GLInstancedSprites::onRender(glm::mat4 proj_view_mat){
	GLuint err;
	// shader switch
	glUseProgram(shaderHnd);
	//glEnable(GL_CULL_FACE);
	glUniformMatrix4fv(viewprojMatrixHnd, 1, GL_FALSE, &proj_view_mat[0][0]);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// texture setup
	glActiveTexture(GL_TEXTURE0);
	//auto it = textureIds.begin();
	glBindTexture(GL_TEXTURE_2D, textureId);
	glUniform1i(samplerVarHnd, 0);

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
		2,
		GL_FLOAT, 
		GL_FALSE, 
		sizeof(SpriteDesc),
		BUFFER_OFFSET(0)
		);
	// rotation scale
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(
		3, 
		2, 
		GL_FLOAT,
		GL_FALSE,
		sizeof(SpriteDesc),
		BUFFER_OFFSET(sizeof(GLfloat) * 2)
		);
	// instance uv
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(
		4,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(SpriteDesc),
		BUFFER_OFFSET(sizeof(GLfloat) * 4)
		);
	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 0);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, sprite_count);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	err = glGetError();
}
GLuint GLInstancedSprites::createTexture(unsigned int width, unsigned int height, const unsigned char* initialData){
	GLuint texId;
	glGenTextures(1, &texId);
	//textureIDs.push(texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, initialData);
	GLuint err = glGetError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	err = glGetError();
	return texId;
}
//
GLuint GLInstancedSprites::initShaders(const char* vertex_file_path, const char* fragment_file_path) {
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

	samplerVarHnd = glGetUniformLocation(ProgramID, "myTextureSampler");
	viewprojMatrixHnd = glGetUniformLocation(ProgramID, "mat_view_proj");
	//GLuint err = glGetError();
	return ProgramID;
}
void GLInstancedSprites::useTexture(const char* resourceId, unsigned int _width, unsigned int _height) {
}