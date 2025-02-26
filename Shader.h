#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>; // ���������� glew ��� ����, ����� �������� ��� ����������� ������������ ����� OpenGL

class Shader
{
public:
    // ������������� ���������
    GLuint Program;
    // ����������� ��������� � �������� ������
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // ������������� ���������
    void Use() const;
};
