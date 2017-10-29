#include "GLManager.h"
#include "lodepng/lodepng.h"
#include <assert.h>
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
#include "GLInstancedSprites.h"
#include "GLIMLines.h"

GLManager::GLManager(void) : window(nullptr){
	//ZeroMemory((void*)this, sizeof(GLManager));
	cameraSize = 10.0f;
	cameraPos = Vector2::zero();
}
GLManager::~GLManager()
{
	// close and release all existing COM objects
	// render technique related
	for (int i = 0; i < instancedSprites.length; ++i) {
		instancedSprites[i]->dispose();
		deallocT(instancedSprites[i]);
	}
	deallocT(debugRender);
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
	glfwGetFramebufferSize(window, &width, &height);

	debugRender = newClass<GLIMLines>("GLIMLines class");
	debugRender->init();
	return true;
}

void GLManager::initDepthStencil(){

}
void GLManager::render(){
	GLuint err;
	assembleDrawables();
	prepareCamera();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < instancedSprites.length; ++i) {
		instancedSprites[i]->onRender(proj_view);
	}
	debugRender->onRender(proj_view);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(15, 0, 0);
	glEnd();

	glfwSwapBuffers(window);
	glfwPollEvents();
	err = glGetError();

}
void GLManager::restoreRenderTarget(){
	
}
void GLManager::prepareCamera(){
	//glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	// Or, for an ortho camera :
	float aspect = (float)width / (float)height;
	glm::mat4 proj_mat = glm::ortho(-cameraSize * aspect, cameraSize * aspect,
		-cameraSize, cameraSize,
		0.0f,100.0f); // In world coordinates
	glm::vec3 cam_pos = glm::vec3(cameraPos.x, cameraPos.y, 1);
	glm::vec3 lookat = cam_pos;
	lookat.z -= 1.0f;
	// Camera matrix
	glm::mat4 view_mat = glm::lookAt(
		cam_pos, // Camera's pos in World Space
		lookat, // lookat
		glm::vec3(0, 1, 0)  // up vector (set to 0,-1,0 to look upside-down)
		);

	proj_view = proj_mat * view_mat;
}

void GLManager::assembleDrawables(){
	/*if (instancedMesh == nullptr){
		instancedMesh = new DXInstancedMesh(dev, devcon);
		instancedMesh->init();
	}
	instancedMesh->updateInstanceBuffer(instancedObjects);*/

	for (int i = 0; i < instancedSprites.length; ++i) {
		instancedSprites[i]->updateBufferFromSpriteDesc();
	}
	debugRender->updateBuffer();
}
int GLManager::newSpriteSheet(const char* spritePath) {
	int ret = 0;
	int hash = CharHelper::charHash(spritePath);

	auto it = textureIds.find(hash);
	if (it == textureIds.end()) {
		GLInstancedSprites* newSpriteInstance = newClass<GLInstancedSprites>();
		newSpriteInstance->init();
		newSpriteInstance->newSpriteSheet(spritePath);
		instancedSprites.push(newSpriteInstance);
		ret = instancedSprites.length - 1;
		textureIds.insert(std::pair<unsigned int, int>(hash, ret));
	}
	else {
		ret = it->second;
	}
	return ret;
}
int GLManager::newSprite(int handle, Vector2 pos, Vector2 uv) {
	return instancedSprites[handle]->newSprite(pos, uv);
}
void GLManager::updateSprite(int textureId, int spriteId, Vector2 pos) {
	instancedSprites[textureId]->updateSprite(spriteId, pos);
}
void GLManager::updateSprite(int textureId, int spriteId, Vector2 pos, float angle, Vector2 scale) {
	instancedSprites[textureId]->updateSprite(spriteId, pos, angle, scale);
}
void GLManager::line2D(Vector2 pos0, Vector2 pos1, Color color) {
	debugRender->drawLine(pos0, pos1, color);
}