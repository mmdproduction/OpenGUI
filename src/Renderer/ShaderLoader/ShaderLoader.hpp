#pragma once
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

#include<GL/glew.h>

class ShaderLoader
{
public:
    GLuint id;
    ShaderLoader(const GLchar* vertexPath, const GLchar* fragmentPath);
    use();
};




