#pragma once

#include<vector>
#include<string>
#include"Renderer.hpp"
#include"TextRenderer.hpp"
#include"EventSystem.hpp"

class UIElement{
    protected:
    uint16_t centerX = 0;
    uint16_t centerY = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    public:

    bool isVisiable = false;
    bool isEnable = false;

    UIElement(uint16_t posX, uint16_t posY, uint16_t width, uint16_t height):
    centerX(posX), centerY(posY), width(width), height(height), isVisiable(true), isEnable(true) {}

    virtual ~UIElement() = default;

    virtual void draw(Renderer& render, TextRenderer& textRender) = 0;
    virtual void update() = 0;
    virtual bool onEvent(EventSystem& events) { return false; }
    
    bool contains(float mouseX, float mouseY){
        return (centerX - width / 2) <= mouseX && (centerY - height / 2) <= mouseY &&
        (centerX + width / 2) >= mouseX && (centerY + height / 2) >= mouseY;
    }

    void setPosition(uint16_t newX, uint16_t newY){ centerX = newX; centerY = newY; }
    void setSize(uint16_t newX, uint16_t newY){width = newX; height = newY; }
    void setEnable(bool e){ isEnable = e; }
    void setVisiable(bool v) {isVisiable = v; }



};

class UIButton : protected UIElement {
    private:
    std::string text;
    glm::vec4 backgroundColor;
    glm::vec3 textColor;


    public:
    UIButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, glm::vec4 backColor, const std::string& text, glm::vec3 textColor);
    ~UIButton();
    void draw (Renderer& render, TextRenderer& textRender) override;
    bool onEvent(EventSystem& events) override;
    void update() override;

    bool isHovered;
    bool isPressed;
};



