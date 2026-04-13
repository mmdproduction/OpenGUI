#pragma once

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <map>
#include <string>
#include "ShaderLoader.hpp"


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
    std::map<GLchar, Character> Characters;

    Shader shader;
};