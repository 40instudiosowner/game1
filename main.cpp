// GLEW нужно подключать до GLFW.
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
	// и приложение после этого закроется
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


int main()
{
	glfwInit();  	//Инициализация GLFW

	//Настройка GLFW
	//Задается минимальная требуемая версия OpenGL. 
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Мажорная 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  //Минорная
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  	//Установка профайла для которого создается контекст
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);  	//Выключение возможности изменения размера окна

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
	glViewport(0, 0, width, height); // отрисовать 

	glfwSetKeyCallback(window, key_callback);

	Shader shader("shaders/shader.vs", "shaders/shader.frag");
	

	GLfloat vertices[] =
	{
		0.5f,  0.5f, 0.0f,  // Верхний правый угол
		0.5f, -0.5f, 0.0f,  // Нижний правый угол
		-0.5f, -0.5f, 0.0f,  // Нижний левый угол
		-0.5f,  0.5f, 0.0f   // Верхний левый угол
	};
	GLuint indices[] = 
	{  // Помните, что мы начинаем с 0!
		0, 1, 3,   // Первый треугольник
		1, 2, 3    // Второй треугольник
	};
	GLuint VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// Код инициализации (выполняется единожды (если, конечно, объект не будет часто изменяться)) :: .. 
	// 1. Привязываем VAO;
	glGenVertexArrays(1, &VAO);
	// 2. Копируем наш массив вершин в буфер для OpenGL
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
	// 3. Устанавливаем указатели на вершинные атрибуты 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	//4. Отвязываем VAO
	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // линии

	while (!glfwWindowShouldClose(window)) // игровой цикл
	{
		glfwPollEvents();  // Проверяем события и вызываем функции обратного вызова

		// Команды отрисовки
		glClearColor(0.f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// rectangle
		shader.Use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);  // Меняем буферы местами
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();

	return 0;
}