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

/// @brief Баг с цветом текста (передавать сразу в вершинный шейдер)
class TextRenderer{
    private:
    GLuint VAO = 0,
    VBO = 0;
    std::map<GLuint, Character> characters;
    struct RenderInfo {
        GLuint textureID;
        GLfloat vertices[6][4];
    };
    std::vector<RenderInfo> vecVertices;
    Shader shader;
    glm::mat4 projection;
    glm::vec3 color;

    static std::u32string charToUnicode(const std::string& utf8);
    void drawText(const std::u32string& text, GLfloat x, GLfloat y, GLfloat scale , glm::vec3 color);
    void textFlush();
    public:

    TextRenderer(uint16_t width, uint16_t height, const GLchar* vertexPath, const GLchar* fragmentPath);
    ~TextRenderer();

    bool loadFont(const std::string& fontPath, GLuint fontSize);
    void begin();
    void drawText(const std::string& text, GLfloat x, GLfloat y, GLfloat scale , glm::vec3 color);
    void end();
};