#include"Renderer.hpp"

Renderer::Renderer(uint16_t width, uint16_t height, const GLchar* vertexPath, const GLchar* fragmentPath): shader(vertexPath, fragmentPath){
    projectionMatrics = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
    indices = {
        0, 1, 2, 2, 3, 0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertexBufferMax * sizeof(GUIVertex), nullptr, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

Renderer::~Renderer(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
}

void Renderer::begin(){
    vertices.clear();
}

void Renderer::end(){
    flush();
}

void Renderer::draw(glm::vec2 pos, glm::vec2 size, glm::vec4 color){
    if(vertices.size() <= vertexBufferMax){
        flush();
        vertices.clear();
    }

    float x = pos.x;
    float y = pos.y;
    float w = size.x;
    float h = size.y;

    vertices.push_back({{x, y}, color});         
    vertices.push_back({{x + w, y}, color});    
    vertices.push_back({{x + w, y + h}, color}); 
    vertices.push_back({{x, y + h}, color});    
    
}

void Renderer::flush(){
    if(vertices.empty()) return;

    shader.use();
    shader.setUniformMatrix4("uProjection", projectionMatrics);

    glBindVertexArray(VAO);

   
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(GUIVertex), vertices.data());
    glDrawElements(GL_TRIANGLES, (vertices.size() / 4) * 6, GL_UNSIGNED_INT, 0);
}

void Renderer::resize(uint16_t newWidth, uint16_t newHeight){
    projectionMatrics = glm::ortho(0.0f, (float)newWidth, (float)newHeight, 0.0f, -1.0f, 1.0f);
}