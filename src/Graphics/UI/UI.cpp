#include"UI.hpp"

UIButton::UIButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, glm::vec4 backColor, const std::string& text, glm::vec3 textColor): UIElement(x, y, width, height), text(text), backgroundColor(backColor), textColor(textColor){}
UIButton::~UIButton(){

}

void UIButton::draw(Renderer& render, TextRenderer& textRender){
    if(!isVisiable) return;
    if(isPressed){ render.draw({centerX - width /2, centerY - height/ 2},
        {width, height}, {backgroundColor.x - 0.2f, backgroundColor.y - 0.2f, backgroundColor.z - 0.2f, backgroundColor.w});
        //textRender.drawText(text, centerX - width /2, centerY - height/ 2, 1, textColor);
    }
    else if(isHovered){ render.draw({centerX - width /2, centerY - height/ 2},
        {width, height}, {backgroundColor.x - 0.1f, backgroundColor.y - 0.1f, backgroundColor.z - 0.1f, backgroundColor.w});
        //textRender.drawText(text, centerX - width /2, centerY - height/ 2, 1, textColor);
    }
    else{ render.draw({centerX - width /2, centerY - height/ 2},
        {width, height}, {backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w});
        
    }

    textRender.drawText(text, centerX - width /2, centerY, 1, textColor);
    
}

bool UIButton::onEvent(EventSystem& events){
    if(!isVisiable || !isEnable) return false;
    if(this->contains(events.getMouseX(), events.getMouseY()) && events.isButtonDown(GLFW_MOUSE_BUTTON_LEFT)){
        isPressed = true;
        return true;
    }
    else if (this->contains(events.getMouseX(), events.getMouseY())){ 
        isHovered = true;
        return true;
    }
    return false;
}

void UIButton::update(){
    isPressed = false;
    isHovered = false;
}