#include "GLManager.h"
#include "../lodepng/lodepng.h"
#include <assert.h>
GLManager::GLManager(void){
	//ZeroMemory((void*)this, sizeof(GLManager));
	window = nullptr;
	instancedSprites = nullptr;
	
}
void GLManager::dispose()
{
	// close and release all existing COM objects
	// render technique related
	instancedSprites->dispose();
	Renderer::dispose();
	glfwTerminate();
	
}
bool GLManager::init(HWND hWnd, int _width, int _height)
{

	/* Initialize the library */
	if (!glfwInit())
		return false;


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(_width, _height, "Test RTS", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glewExperimental = true;
	printf_s("console");
	if (glewInit() != GLEW_OK) {
		printf_s("Failed to initialize GLEW\n");
		return false;
	}
	/// refactor this!
	//GLuint VertexArrayID;
	//glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);
	instancedSprites = new	GLInstancedSprites();
	instancedSprites->init();
	instancedSprites->newSpriteSheet(512, 512, "assets/arrows.png");
	instancedSprites->newSprite();
	return true;
}
void GLManager::loadPNG(const IntVector2& _dim, const char* fileName) {
}
void GLManager::initDepthStencil(){

}

void GLManager::renderWithoutShadowMap(){

}
void GLManager::renderWithShadowMap(){
	
}
// render with deferred-shading
void GLManager::platformRender(){
	GLuint err;
	assembleDrawables();

	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Bind our texture in Texture Unit 0
	instancedSprites->onRender();
	/* Swap front and back buffers */
	glfwSwapBuffers(window);
	err = glGetError();
	/* Poll for and process events */
	glfwPollEvents();
	err = glGetError();

}
void GLManager::restoreRenderTarget(){
	
}
void GLManager::prepareCamera(){
	
}

void GLManager::assembleDrawables(){
	/*if (instancedMesh == nullptr){
		instancedMesh = new DXInstancedMesh(dev, devcon);
		instancedMesh->init();
	}
	instancedMesh->updateInstanceBuffer(instancedObjects);

	if (instancedSprites == nullptr){
		instancedSprites = new DXInstancedSprite(dev, devcon);
		instancedSprites->init();
	}
	instancedSprites->updateInstanceBuffer(spriteObjects);*/

}
//int GLManager::createTexture(unsigned int width, unsigned int height, const unsigned char* initialData){
//	int ret = 0;
//
//	
//	glGenTextures(1, &textureID);
//
//	// "Bind" the newly created texture : all future texture functions will modify this texture
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, initialData);
//	GLuint err = glGetError();
//	// Read the file, call glTexImage2D with the right parameters
//	//glTexImage2D(initialData, 0);
//
//	// Nice trilinear filtering.
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glGenerateMipmap(GL_TEXTURE_2D);
//
//	err = glGetError();
//	return ret;
//}
////
//GLuint GLManager::loadShaders(const char* vertex_file_path, const char* fragment_file_path) {
//	CharBuffer* vshaderCode = CharHelper::loadTextFile(vertex_file_path);
//	CharBuffer* fshaderCode = CharHelper::loadTextFile(fragment_file_path);
//	// Create the shaders
//	GLuint vshaderHnd = glCreateShader(GL_VERTEX_SHADER);
//	GLuint fshaderHnd = glCreateShader(GL_FRAGMENT_SHADER);
//
//	// Read the Fragment Shader code from the file
//	GLint Result = GL_FALSE;
//	int InfoLogLength;
//
//
//	// Compile Vertex Shader
//	printf("Compiling vshader : %s\n", vertex_file_path);
//	glShaderSource(vshaderHnd, 1, &vshaderCode->buffer, NULL);
//	glCompileShader(vshaderHnd);
//
//	// Check Vertex Shader
//	glGetShaderiv(vshaderHnd, GL_COMPILE_STATUS, &Result);
//	glGetShaderiv(vshaderHnd, GL_INFO_LOG_LENGTH, &InfoLogLength);
//	if (InfoLogLength > 0) {
//		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
//		char msg[255];
//		//glGetShaderInfoLog(vshaderHnd, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
//		glGetShaderInfoLog(vshaderHnd, InfoLogLength, NULL, msg);
//		printf("%s\n", &VertexShaderErrorMessage[0]);
//	}
//
//
//	// Compile Fragment Shader
//	printf("Compiling fshader : %s\n", fragment_file_path);
//	glShaderSource(fshaderHnd, 1, &fshaderCode->buffer, NULL);
//	glCompileShader(fshaderHnd);
//
//	// Check Fragment Shader
//	glGetShaderiv(fshaderHnd, GL_COMPILE_STATUS, &Result);
//	glGetShaderiv(fshaderHnd, GL_INFO_LOG_LENGTH, &InfoLogLength);
//	if (InfoLogLength > 0) {
//		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
//		glGetShaderInfoLog(fshaderHnd, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
//		printf("%s\n", &FragmentShaderErrorMessage[0]);
//	}
//
//	// Link the program
//	printf("Linking program\n");
//	GLuint ProgramID = glCreateProgram();
//	glAttachShader(ProgramID, vshaderHnd);
//	glAttachShader(ProgramID, fshaderHnd);
//	glLinkProgram(ProgramID);
//
//	// Check the program
//	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
//	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
//	if (InfoLogLength > 0) {
//		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
//		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
//		printf("%s\n", &ProgramErrorMessage[0]);
//	}
//	
//	glDetachShader(ProgramID, vshaderHnd);
//	glDetachShader(ProgramID, fshaderHnd);
//
//	
//
//	glDeleteShader(vshaderHnd);
//	glDeleteShader(fshaderHnd);
//	vshaderCode->dispose();
//	fshaderCode->dispose();
//
//	samplerVarHnd = glGetUniformLocation(ProgramID, "myTextureSampler");
//	//GLuint err = glGetError();
//	return ProgramID;
//}