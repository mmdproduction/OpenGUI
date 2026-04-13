#pragma once
#include"../ShaderLoader/ShaderLoader.hpp"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

struct GUIVertex {
    glm::vec2 position;
    glm::vec4 color;
};

class Renderer{
    private:
    GLuint VAO = 0,
    VBO = 0,
    IBO = 0;
    size_t vertexBufferMax = 10000;

    glm::mat4 projectionMatrics;

    std::vector<GUIVertex> vertices;
    std::vector<uint32_t> indices;

    Shader shader;

    void flush();

    public:

    Renderer(uint16_t width, uint16_t height, const GLchar* vertexPath, const GLchar* fragmentPath);
    ~Renderer();

    void begin();
    void end();

    void draw(glm::vec2 pos, glm::vec2 size, glm::vec4 color);

    //void resize(uint16_t newWidth, uint16_t newHeigth);



};