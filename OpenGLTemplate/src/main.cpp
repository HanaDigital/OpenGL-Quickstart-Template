#include "core.h"
#include "engine/window.h"
#include "engine/input.h"
#include "engine/shader.h"

void terminateGLFW();

int main() {
	const int windowWidth = 1920;
	const int windowHeight = 1080;
	const bool fullScreenMode = false;

	// Create Window
	const bool success = OGLWindow::createWindow(windowWidth, windowHeight, "OpenGL Template", fullScreenMode);
	if (!success) return -1;

	// Initialize shader
	// Remember to delete shaders created this way at the end
	OGLShader::Shader* shader = NULL;
	try { shader = new OGLShader::Shader("assets/shaders/vertexShader.glsl", "assets/shaders/fragmentShader.glsl"); }
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		terminateGLFW();
		return -1;
	}

	// Create vertices for a square
	// Update Vertex in shader.h to add more attributes
	OGLShader::Vertex vertices[] = {
		// Postion							// Color
		{ glm::vec3(0.5f, -0.5f, 0.0f),		glm::vec4(0.9f, 0.8f, 0.2f, 1.0f) },	// 0 Bottom Right
		{ glm::vec3(0.5f, 0.5f, 0.0f),		glm::vec4(0.2f, 0.9f, 0.8f, 1.0f) },	// 1 Top Right
		{ glm::vec3(-0.5f, 0.5f, 0.0f),		glm::vec4(0.8f, 0.2f, 0.9f, 1.0f) },	// 2 Top Left
		{ glm::vec3(-0.5f, -0.5f, 0.0f),	glm::vec4(0.8f, 0.9f, 0.2f, 1.0f) },	// 3 Bottom Left
	};
	// Automaticall calculate required data
	const int vertexLen = sizeof(OGLShader::Vertex) / sizeof(float);
	int vertexByteSize = sizeof(vertices);
	const int vertexCount = vertexByteSize / vertexLen / sizeof(float);
	// Set usage type GL_STATIC_DRAW, GL_DYNAMIC_DRAW, etc.
	int usage = GL_STATIC_DRAW;

	// Create the indices
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	int indicesByteSize = sizeof(indices);
	const int indicesLen = indicesByteSize / sizeof(unsigned int);

	// Create VBO
	unsigned int vaoID = OGLShader::createVAO();
	OGLShader::createVBO(vertices, vertexByteSize, vertexLen, usage);
	OGLShader::createEBO(indices, indicesByteSize, usage);
	OGLShader::addVertexAttrib(0, 3, vertexLen, (void*)offsetof(OGLShader::Vertex, position));	// Position
	OGLShader::addVertexAttrib(1, 4, vertexLen, (void*)offsetof(OGLShader::Vertex, color));		// Color

	// Set clear color
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// Main loop
	while (!glfwWindowShouldClose(OGLWindow::nativeWindow)) {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// Handle input
		OGLInput::handleKeyInput();

		// Render
		OGLShader::useVAO(vaoID);
		shader->use();
		//glDrawArrays(GL_TRIANGLES, 0, vertexCount);
		glDrawElements(GL_TRIANGLES, indicesLen, GL_UNSIGNED_INT, 0);

		// Swap buffers & Handle window events
		glfwSwapBuffers(OGLWindow::nativeWindow);
		glfwPollEvents();
	}

	// Terminate
	delete shader;
	terminateGLFW();
	return 0;
}

void OGLInput::handleKeyInput() {
	if (OGLInput::isKeyDown(GLFW_KEY_ESCAPE)) {
		OGLWindow::close();
	}
}

void terminateGLFW() {
	glfwDestroyWindow(OGLWindow::nativeWindow);
	glfwTerminate();
}