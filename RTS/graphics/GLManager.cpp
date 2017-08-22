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
	deallocT(instancedSprites);
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

	if (glewInit() != GLEW_OK) {
		printf_s("Failed to initialize GLEW\n");
		return false;
	}
	instancedSprites = alloc<GLInstancedSprites>();
	instancedSprites->init();
	instancedSprites->newSpriteSheet(512, 512, "assets/arrows.png");
	instancedSprites->newSprite(Vector2(0.5, 0), Vector2(7, 0));
	instancedSprites->newSprite(Vector2(-0.5, -0.5), Vector2(1, 0));
	instancedSprites->newSprite(Vector2(0.5, -0.5), Vector2(1, 0));
	instancedSprites->newSprite(Vector2(-1.5, -0.5), Vector2(1, 0));
	instancedSprites->newSprite(Vector2(-0.5, -1.5), Vector2(1, 0));
	//instancedSprites->newSprite();
	return true;
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
	prepareCamera();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




	instancedSprites->onRender(proj_view);
	glLineWidth(2.5);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(15, 0, 0);
	glEnd();
	glfwSwapBuffers(window);
	glfwPollEvents();

}
void GLManager::restoreRenderTarget(){
	
}
void GLManager::prepareCamera(){
	//glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	// Or, for an ortho camera :
	glm::mat4 proj_mat = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Camera matrix
	glm::mat4 view_mat = glm::lookAt(
		glm::vec3(0, 0, 1), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

	proj_view = proj_mat * view_mat;
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

void GLManager::newSpriteSheet(unsigned int width, unsigned int height, const char* spritePath) {
	instancedSprites->newSpriteSheet(width, height, spritePath);
}
void GLManager::newSprite(const Vector2 pos, const Vector2 uv) {
	instancedSprites->newSprite(pos, uv);
}