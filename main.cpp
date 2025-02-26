// GLEW ����� ���������� �� GLFW.
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// ����� ������������ �������� ESC, �� ������������� �������� WindowShouldClose � true, 
	// � ���������� ����� ����� ���������
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


int main()
{
	glfwInit();  	//������������� GLFW

	//��������� GLFW
	//�������� ����������� ��������� ������ OpenGL. 
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //�������� 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  //��������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  	//��������� �������� ��� �������� ��������� ��������
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);  	//���������� ����������� ��������� ������� ����

	GLFWwindow* window = glfwCreateWindow(800, 600, "Game 1", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)  // Initialize GLEW to setup the OpenGL Function pointers
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height); // get width & height from window by reference
	glViewport(0, 0, width, height); // ���������� 

	glfwSetKeyCallback(window, key_callback);

	Shader shader("shaders/shader.vs", "shaders/shader.frag");
	

	GLfloat vertices[] =
	{
		0.5f,  0.5f, 0.0f,  // ������� ������ ����
		0.5f, -0.5f, 0.0f,  // ������ ������ ����
		-0.5f, -0.5f, 0.0f,  // ������ ����� ����
		-0.5f,  0.5f, 0.0f   // ������� ����� ����
	};
	GLuint indices[] = 
	{  // �������, ��� �� �������� � 0!
		0, 1, 3,   // ������ �����������
		1, 2, 3    // ������ �����������
	};
	GLuint VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// ��� ������������� (����������� �������� (����, �������, ������ �� ����� ����� ����������)) :: .. 
	// 1. ����������� VAO;
	glGenVertexArrays(1, &VAO);
	// 2. �������� ��� ������ ������ � ����� ��� OpenGL
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
	// 3. ������������� ��������� �� ��������� �������� 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	//4. ���������� VAO
	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // �����

	while (!glfwWindowShouldClose(window)) // ������� ����
	{
		glfwPollEvents();  // ��������� ������� � �������� ������� ��������� ������

		// ������� ���������
		glClearColor(0.f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// rectangle
		shader.Use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);  // ������ ������ �������
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();

	return 0;
}