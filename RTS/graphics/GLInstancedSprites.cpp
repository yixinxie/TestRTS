#include "GLInstancedSprites.h"
#include "../lodepng/lodepng.h"
#include <assert.h>
GLInstancedSprites::GLInstancedSprites(void){
	//ZeroMemory((void*)this, sizeof(GLInstancedSprites));
	window = nullptr;
	vertexbuffer = 0;
}
void GLInstancedSprites::dispose(){
}
void GLInstancedSprites::init(){
	shaderHnd = initShaders("shaders/sprite_vs.glsl", "shaders/sprite_fs.glsl");
}
void GLInstancedSprites::newSprite(unsigned int width, unsigned int height, const char* spritePath){

	/// refactor this!
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	

	glUseProgram(shaderHnd);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f,	0.0f, 0.0,	0.0,
		1.0f, -1.0f,	0.0f, 1,	0,
		-1.0f,  1.0f,	0.0f, 0,	1,

		-1.0f,  1.0f,	0.0f, 0,	1,
		
		1.0f, -1.0f,	0.0f, 1,	0,
		1.0f, 1.0f,		0.0f, 1,	1,
		
		
	};
	// This will identify our vertex buffer
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
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
	createTexture(width, height, image.data());

}
void GLInstancedSprites::onRender(){
	GLuint err;
	/* Render here */
	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	err = glGetError();
	glBindTexture(GL_TEXTURE_2D, textureID);
	err = glGetError();
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(samplerVarHnd, 0);
	err = glGetError();

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	err = glGetError();
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	err = glGetError();
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(GL_FLOAT) * 5,                  // stride
		//(void*)0            // array buffer offset
		(void*)0
		);

	err = glGetError();
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(GL_FLOAT) * 5,                  // stride
		//BUFFER_OFFSET(12)            // array buffer offset
		(void*)(sizeof(GL_FLOAT) * 3)
		);
	err = glGetError();
	

	//glBindBuffer(GL_TEXTURE_2D, textureID);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices total -> 1 triangle
	err = glGetError();
	glDisableVertexAttribArray(0);
	err = glGetError();


}
int GLInstancedSprites::createTexture(unsigned int width, unsigned int height, const unsigned char* initialData){
	int ret = 0;

	
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, initialData);
	GLuint err = glGetError();
	// Read the file, call glTexImage2D with the right parameters
	//glTexImage2D(initialData, 0);

	// Nice trilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	err = glGetError();
	return ret;
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
	//GLuint err = glGetError();
	return ProgramID;
}