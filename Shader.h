#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>; // Подключаем glew для того, чтобы получить все необходимые заголовочные файлы OpenGL

class Shader
{
public:
    // Идентификатор программы
    GLuint Program;
    // Конструктор считывает и собирает шейдер
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // Использование программы
    void Use() const;
};
