// GLEW ����� ���������� �� GLFW.
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <iostream>


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// ����� ������������ �������� ESC, �� ������������� �������� WindowShouldClose � true, 
	// � ���������� ����� ����� ���������
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


int main()
{
	//������������� GLFW
	glfwInit();
	//��������� GLFW
	//�������� ����������� ��������� ������ OpenGL. 
	//�������� 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//��������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//��������� �������� ��� �������� ��������� ��������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//���������� ����������� ��������� ������� ����
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	GLFWwindow* window = glfwCreateWindow(800, 600, "Game 1", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);


	int width, height;
	glfwGetFramebufferSize(window, &width, &height); // get width & height from window by reference

	glViewport(0, 0, width, height); // ���������� 

	while (!glfwWindowShouldClose(window)) // ������� ����
	{

		glfwPollEvents();  // ��������� ������� � �������� ������� ��������� ������

		// ������� ���������
		glClearColor(0.f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glfwSwapBuffers(window);  // ������ ������ �������
	}

	glfwTerminate();

	return 0;
}