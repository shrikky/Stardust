#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "SDShader.h"
using namespace std;

void frameBuffer_Size_Callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create Window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << " Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBuffer_Size_Callback);
	// Initialize Glad

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << " Failed to init GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader program
	// ------------------------------------
	Shader ourShader; // you can name your shader files however you like
	ourShader.CompileShader("F:/Stardust/Stardust/Stardust/Shaders/VertexShader.glsl", Shader::ShaderType::VERTEX);
	ourShader.CompileShader("F:\\Stardust\\Stardust\\Stardust\\Shaders\\FragmentShader.glsl", Shader::ShaderType::FRAGMENT);
	// set up vertex data (and buffer(s)) and configure vertex attributes

	float vertices[] = {
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. then set the vertex attributes pointers

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	ourShader.Use();

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// render the triangle


		float timeValue = glfwGetTime();
		float greenvalue = sin(timeValue) / 2 + 0.5f;
		int vertexLocation = glGetUniformLocation(ourShader.GetShaderProgramID(), "ourColor");
		glUniform4f(vertexLocation, 0.0f, greenvalue, 0.0f, 1.0f);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;

}

void frameBuffer_Size_Callback(GLFWwindow* window, int width, int height) 
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}