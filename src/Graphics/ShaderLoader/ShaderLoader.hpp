#pragma once
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

#include<GL/glew.h>
#include<glm/gtc/matrix_transform.hpp>

class Shader
{
    private:
    GLuint id;

    public:
    
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    ~Shader();
    void use();
    void setUniformMatrix4(const std::string& name, glm::mat4& matrics) const;
    GLuint getId();

};




