#include "GLInstancedSprites.h"
#include "lodepng/lodepng.h"
#include "cimg/CImg.h"
#include <assert.h>
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
GLInstancedSprites::GLInstancedSprites(void){
	
}
void GLInstancedSprites::dispose(){

	GLuint disposeBuffers[2];
	disposeBuffers[0] = instance_buffer;
	disposeBuffers[1] = vertex_buffer;
	glDeleteBuffers(2, disposeBuffers);

	//deallocND(spriteDesc);
}
void GLInstancedSprites::init(){
	vertex_buffer = 0;
	instance_buffer = 0;

	//sprite_count = 0;
	sprite_max = 0;
	//spriteDesc = allocArray<SpriteDesc>(sprite_max, "init");

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	shaderHnd = initShaders("shaders/sprite_vs.glsl", "shaders/sprite_fs.glsl");

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f,	0.0f, 0.0f,	0.0f,
		1.0f, -1.0f,	0.0f, 1.0f,	0.0f,
		-1.0f,  1.0f,	0.0f, 0.0f,	1.0f,
		1.0f, 1.0f,		0.0f, 1.0f,	1.0f,


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
GLuint GLInstancedSprites::newSpriteSheet(const char* spritePath){
	unsigned char* imageBuffer;
	unsigned int w, h;
	unsigned int error = 0;
	std::vector<unsigned char> image;
	if (CharHelper::charEndsWith(spritePath, "png")) {
		std::vector<unsigned char> pngData; //the raw pixels
		
		lodepng::State load_state;

		//lodepng::decode(image, w, h, load_state);
		error = lodepng::load_file(pngData, spritePath);
		assert(error == 0);
		error = lodepng::decode(image, w, h, pngData);
		CharBuffer* uvTxtBuffer = CharHelper::loadTextFile("assets/terrain_packed.txt");
		std::vector<SpriteSheetUV> uvDesc;
		CharHelper::parseUVTxt(uvTxtBuffer->buffer, uvDesc);
		for (int i = 0; i < uvDesc.size(); ++i) {
			uvDesc[i].left_bottom.x /= (float)w;
			uvDesc[i].left_bottom.y /= (float)h;

			uvDesc[i].right_top.x /= (float)w;
			uvDesc[i].right_top.y /= (float)h;
		}
		int sdf = 0;
		uvTxtBuffer->dispose();
	}
	else if (CharHelper::charEndsWith(spritePath, "jpg")) {
		cimg_library::CImg<unsigned char> jpg_image(spritePath);
		imageBuffer = jpg_image.data();
	}
	else {
		// unrecognized file format
		assert(false);
		return 0;
	}
	
	assert(error == 0);
	imageBuffer = image.data();
	// create texture in GPU.
	textureId = createTexture(w, h, image.data());
	return textureId;

}
int GLInstancedSprites::newSprite(Vector2 pos, Vector2 uv) {
	GLuint er;
	int cur = spriteDesc.length;
	const float unitUV = 1.0f / 12.0f;
	SpriteDesc newDesc;
	newDesc.pos = pos;
	newDesc.rotation = 0;
	newDesc.scale = Vector2(1, 1);
	newDesc.uv.x = uv.x * unitUV;
	newDesc.uv.y = uv.y * unitUV;
	spriteDesc.push(newDesc);
	return cur;
}
void GLInstancedSprites::updateSprite(int spriteId, Vector2 pos) {
	spriteDesc[spriteId].pos = pos;
}
void GLInstancedSprites::updateSprite(int spriteId, Vector2 pos, float angle, Vector2 scale) {
	spriteDesc[spriteId].pos = pos;
	spriteDesc[spriteId].rotation = angle;
	spriteDesc[spriteId].scale = scale;

}
void GLInstancedSprites::updateBufferFromSpriteDesc() {
	if (spriteDesc.allocatedSize() != sprite_max) {

		if (sprite_max != 0) {
			GLuint singleBuffer[1];
			singleBuffer[0] = instance_buffer;
			glDeleteBuffers(1, singleBuffer);
		}

		glGenBuffers(1, &instance_buffer);
		sprite_max = spriteDesc.allocatedSize();
	}
	glBindBuffer(GL_ARRAY_BUFFER, instance_buffer);
	glBufferData(GL_ARRAY_BUFFER, sprite_max * sizeof(SpriteDesc), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, sprite_max * sizeof(SpriteDesc), spriteDesc.getPtr());
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
	// rotation
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(
		3,
		1,
		GL_FLOAT,
		GL_FALSE,
		sizeof(SpriteDesc),
		BUFFER_OFFSET(sizeof(GLfloat) * 2)
		);
	// scale
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(
		4, 
		2, 
		GL_FLOAT,
		GL_FALSE,
		sizeof(SpriteDesc),
		BUFFER_OFFSET(sizeof(GLfloat) * 3)
		);
	// instance uv
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(
		5,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(SpriteDesc),
		BUFFER_OFFSET(sizeof(GLfloat) * 5)
		);

	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 0);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, spriteDesc.length);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
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
