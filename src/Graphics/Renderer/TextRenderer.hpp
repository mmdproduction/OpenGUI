#pragma once

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <map>
#include <string>
#include "../ShaderLoader/ShaderLoader.hpp"


struct Character{
    GLuint textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    GLuint advance;
};


class TextRenderer{
    private:
    GLuint VAO = 0,
    VBO = 0;
    std::map<GLuint, Character> characters;
    Shader shader;
    glm::mat4 projection;

    static std::u32string charToUnicode(const std::string& utf8);
    void drawText(const std::u32string& text, GLfloat x, GLfloat y, GLfloat scale , glm::vec3 color);
    public:

    TextRenderer(uint16_t width, uint16_t height, const GLchar* vertexPath, const GLchar* fragmentPath);
    ~TextRenderer();

    bool loadFont(const std::string& fontPath, GLuint fontSize);
    void drawText(const std::string& text, GLfloat x, GLfloat y, GLfloat scale , glm::vec3 color);
};