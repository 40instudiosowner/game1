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

const GLchar* vertexShaderSource{
	"#version 330 core\nlayout(location = 0) in vec3 position;\nvoid main()\n{\ngl_Position = vec4(position.x, position.y, position.z, 1.0);\n}\n\0"
}; // source code vertex shader
const GLchar* fragmentShaderSource{
	"#version 330 core\nout vec4 color;\nvoid main()\n{\ncolor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n}\n\0"
}; // source code fragment shader


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
	// Initialize GLEW to setup the OpenGL Function pointers
	//glewInit();
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	int width, height;
	glfwGetFramebufferSize(window, &width, &height); // get width & height from window by reference
	glViewport(0, 0, width, height); // ���������� 


	glfwSetKeyCallback(window, key_callback);


	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint success; // check the build
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint fragmentShader;  // fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::LINK::SHADERS::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);   // ����� ���������� ������ �� �����
	glDeleteShader(fragmentShader);

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
	// ..:: ��� ������������� (����������� �������� (����, �������, ������ �� ����� ����� ����������)) :: .. 
	// 1. ����������� VAO;
	glGenVertexArrays(1, &VAO);
	// 2. �������� ��� ������ ������ � ����� ��� OpenGL
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 3. ������������� ��������� �� ��������� �������� 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	//4. ���������� VAO
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 2 ��������

	while (!glfwWindowShouldClose(window)) // ������� ����
	{

		glfwPollEvents();  // ��������� ������� � �������� ������� ��������� ������

		// ������� ���������
		glClearColor(0.f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// rectangle
		glUseProgram(shaderProgram);
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