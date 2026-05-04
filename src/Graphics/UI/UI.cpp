#include"UI.hpp"
#include <algorithm>

UIButton::UIButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, glm::vec4 backColor, const std::string& text, glm::vec3 textColor): UIWidget(x, y, width, height), text(text), backgroundColor(backColor), textColor(textColor){}
UIButton::~UIButton(){

}

void UIButton::draw(Renderer& render, TextRenderer& textRender){
    if(!isVisible) return;
    if(isPressed){ render.draw({centerX - width /2, centerY - height/ 2},
        {width, height}, {backgroundColor.x - 0.2f, backgroundColor.y - 0.2f, backgroundColor.z - 0.2f, backgroundColor.w});
        }
    else if(isHovered){ render.draw({centerX - width /2, centerY - height/ 2},
        {width, height}, {backgroundColor.x - 0.1f, backgroundColor.y - 0.1f, backgroundColor.z - 0.1f, backgroundColor.w});
        }
    else{ render.draw({centerX - width /2, centerY - height/ 2},
        {width, height}, {backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w});
        
    }

    textRender.drawText(text, centerX - textRender.getTextWidth(text)/2, centerY - textRender.getLineHeight() / 2.0f + textRender.getAscent(), 1, textColor);
    
}

bool UIButton::onEvent(EventSystem& events){
    if(!isVisible || !isEnable) return false;
    if(contains(events.getMouseX(), events.getMouseY()) && events.isButtonDown(GLFW_MOUSE_BUTTON_LEFT)){
        isPressed = true;
        if(onClicked){
            //onClicked();
        }
        return true;
    }
    else if (contains(events.getMouseX(), events.getMouseY())){ 
        isHovered = true;
        return true;
    }
    return false;
}

void UIButton::setOnClicked(std::function<void(int)> callback){
    onClicked = std::move(callback);
}

void UIButton::update(float){
    isPressed = false;
    isHovered = false;
}

void UIText::draw(Renderer& r, TextRenderer& tr) {
        if (!isVisible) return;
        
        float baselineY = centerY - tr.getLineHeight() / 2.0f + tr.getAscent(); 
        tr.drawText(text, centerX, baselineY, fontSize / tr.getFontSize(), color);
    } 
void UIText::setText(const std::string& t) { 
        text = t; 
        
    }

const std::string& UIText::getText() const { return text; }

void UIText::setFontSize(float s) { fontSize = s; height = s; }


UIInputText::UIInputText(float x, float y, float w, float h, 
                const std::string& placeholder, float fontSize)
        : UIWidget(x, y, w, h), placeholder(placeholder), fontSize(fontSize) { 
        }

void UIInputText::update(float dt) {
        if (focused) {
            cursorBlinkTimer += dt;
            if (cursorBlinkTimer > 0.5f) {
                cursorBlinkTimer = 0.0f;
                showCursor = !showCursor;
            }
        }
    }

void UIInputText::draw(Renderer& r, TextRenderer& tr)  {
    glEnable(GL_SCISSOR_TEST);
    glScissor(centerX - width / 2, centerY - height / 2, width, height);
        if (!isVisible) return;

        glm::vec4 bg = focused ? glm::vec4(0.2f, 0.25f, 0.35f, 1.0f) 
                               : glm::vec4(0.15f, 0.15f, 0.2f, 1.0f);
        r.draw({centerX - width / 2, centerY - height / 2}, {width, height}, bg);
        if(placeholderUnicode.empty()) placeholderUnicode = TextRenderer::charToUnicode(placeholder);
        const std::u32string& displayText = text.empty() ? placeholderUnicode : text;
        glm::vec3 txtColor = text.empty() ? glm::vec3(0.5f) : textColor;
        
        float baselineY = centerY  - tr.getLineHeight() / 2 + tr.getAscent();
        tr.drawText(displayText, centerX - width / 2 + 3.0f, baselineY, 1.0f, txtColor);
        

        if (focused && showCursor) {
            float cursorX = centerX + tr.getTextWidth(text.substr(0, cursorPos)) - width / 2 + 3.0f;
            r.draw({cursorX, baselineY}, {3.0f, tr.getLineHeight() * 0.4f}, {1,1,1,1});
        }
        r.end();
        tr.textFlush();
        glDisable(GL_SCISSOR_TEST);
    }


bool UIInputText::onEvent(EventSystem& events) {
        if (!isVisible || !isEnable) return false;

        bool isInside = contains(events.getMouseX(), events.getMouseY());
        
        if (isInside && events.isButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
            focused = true;
            return true;
        } else if (!isInside && events.isButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
            focused = false;
        }

        if (!focused) return false;

        for(const auto& c : events.getTypedChar()){
            if (c != 0) {
                text.insert(cursorPos, 1, c);
                cursorPos++;
                return true;
            }
        }

        if (events.isKeyPressed(GLFW_KEY_BACKSPACE) && cursorPos > 0) {
            text.erase(cursorPos - 1, 1);
            cursorPos--;
            return true;
        }
        

 
        if (events.isKeyPressed(GLFW_KEY_LEFT) && cursorPos > 0) cursorPos--;
        if (events.isKeyPressed(GLFW_KEY_RIGHT) && cursorPos < text.length()) cursorPos++;

        return false;
    }



UIList::UIList(float x, float y, float w, float h, float itemHeight)
    : UIWidget(x, y, w, h), itemHeight(itemHeight) {
}

void UIList::update(float dt) {
    updateScrollRange();
    scrollOffset = std::clamp(scrollOffset, 0.0f, maxScroll);
}

void UIList::draw(Renderer& r, TextRenderer& tr) {
    if (!isVisible) return;

    float listLeft   = centerX - width / 2.0f;
    float listRight  = centerX + width / 2.0f;
    float listBottom = centerY - height / 2.0f;
    float listTop    = centerY + height / 2.0f;

    r.draw({listLeft, listBottom}, {width, height}, {0.1f, 0.1f, 0.15f, 1.0f});
    r.end();

    int fbW, fbH, winW, winH;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &fbW, &fbH);
    glfwGetWindowSize(glfwGetCurrentContext(), &winW, &winH);

    float scaleX = (float)fbW / winW;
    float scaleY = (float)fbH / winH;

    int scissorX = (int)(listLeft * scaleX);
    int scissorY = (int)(listBottom * scaleY);
    int scissorW = (int)(width * scaleX);
    int scissorH = (int)(height * scaleY);

    glScissor(scissorX, scissorY, scissorW, scissorH);
    glEnable(GL_SCISSOR_TEST);

    float contentWidth = width;
    if (showScrollbar && maxScroll > 0.001f) {
        contentWidth -= scrollbarWidth;
    }


    for (size_t i = 0; i < items.size(); ++i) {

        float itemTopY    = listTop - (i * itemHeight) + scrollOffset;
        float itemBottomY = itemTopY - itemHeight; 
        float itemCenterY = itemBottomY + itemHeight / 2.0f; 


        if (itemTopY < listBottom || itemBottomY > listTop) continue;

        glm::vec4 bgColor;
        if (static_cast<int>(i) == selectedIndex) {
            bgColor = {0.2f, 0.4f, 0.7f, 1.0f};
        } else if (static_cast<int>(i) == hoveredItem) {
            bgColor = {0.25f, 0.25f, 0.35f, 1.0f};
        } else {
            bgColor = (i % 2 == 0) ? glm::vec4(0.12f, 0.12f, 0.18f, 1.0f) 
                                   : glm::vec4(0.15f, 0.15f, 0.20f, 1.0f);
        }

        float itemCenterX = listLeft + contentWidth / 2.0f;
        r.draw({listLeft, itemBottomY}, {contentWidth, itemHeight}, bgColor);

        const auto& itemText = items[i];
        float textX     = listLeft + 10; 
        float baselineY = itemBottomY + (itemHeight * 0.35f);

        tr.drawText(itemText, textX, baselineY, 1.0f, {0.9f, 0.9f, 0.9f});
    }


    r.end();
    tr.textFlush();

    glDisable(GL_SCISSOR_TEST);

    if (showScrollbar && maxScroll > 0.001f) {
        float thumbHeight = std::max(30.0f, height * (height / (items.size() * itemHeight)));
        thumbHeight = std::min(thumbHeight, height - 4.0f);

        float scrollRatio = scrollOffset / maxScroll;
        float thumbBottomY = listBottom - scrollRatio * (height - thumbHeight) + height - thumbHeight;
        float thumbCenterY = thumbBottomY;
        float scrollbarX   = listRight - scrollbarWidth;

        r.draw({listRight - scrollbarWidth, listBottom}, {scrollbarWidth, height}, {0.08f, 0.08f, 0.12f, 1.0f});

        r.draw({scrollbarX, thumbCenterY}, {scrollbarWidth, thumbHeight}, {0.35f, 0.35f, 0.45f, 1.0f});
    }
    r.end();

}
bool UIList::onEvent(EventSystem& events) {
    if (!isVisible || !isEnable) return false;

    bool inside = contains(events.getMouseX(), events.getMouseY());
    if (!inside) return false;

    bool isHandled = false;

    float scrollY = events.getScrollY();
    if (scrollY != 0.0f) {
        scrollOffset -= scrollY * 30.0f;
        scrollOffset = std::clamp(scrollOffset, 0.0f, maxScroll);
        isHandled = true;
    }

    if (events.isButtonClicked(GLFW_MOUSE_BUTTON_LEFT)) {
        int clickedIndex = getItemAtPosition(events.getMouseY());
        
        if (clickedIndex >= 0 && static_cast<size_t>(clickedIndex) < items.size()) {
            float mouseX = events.getMouseX();
            float scrollbarX = centerX + width / 2 - scrollbarWidth;
            
            if (showScrollbar && maxScroll > 0 && mouseX >= scrollbarX) {
                return true;
            }
            
            selectedIndex = clickedIndex;
            hoveredItem = clickedIndex;
            
            if (onItemClicked) {
                onItemClicked(selectedIndex);
            }
            
            isHandled = true;
        }
    }

    if (!isHandled) {
        hoveredItem = getItemAtPosition(events.getMouseY());
    }

    return isHandled;
}

void UIList::addItem(const std::string& text) {
    items.push_back(TextRenderer::charToUnicode(text));
    updateScrollRange();
}

void UIList::addItems(const std::vector<std::string>& texts) {
    for (const auto& text : texts) {
        items.push_back(TextRenderer::charToUnicode(text));
    }
    updateScrollRange();
}

void UIList::removeItem(size_t index) {
    if (index < items.size()) {
        items.erase(items.begin() + index);
        if (selectedIndex >= static_cast<int>(items.size())) {
            selectedIndex = static_cast<int>(items.size()) - 1;
        }
        updateScrollRange();
    }
}

void UIList::clearItems() {
    items.clear();
    scrollOffset = 0.0f;
    maxScroll = 0.0f;
    selectedIndex = -1;
    hoveredItem = -1;
}

const std::u32string& UIList::getItemText(size_t index) const {
    static const std::u32string empty;
    if (index < items.size()) {
        return items[index];
    }
    return empty;
}

void UIList::setOnItemClicked(std::function<void(int)> callback) {
    onItemClicked = std::move(callback);
}

void UIList::updateScrollRange() {
    float contentHeight = items.size() * itemHeight;
    maxScroll = std::max(0.0f, contentHeight - height);
}

float UIList::getItemCenterY(size_t index) const {
    float listTop = centerY + height / 2;
    float itemTop = listTop - (index * itemHeight) + scrollOffset;
    return itemTop - itemHeight / 2;
}

int UIList::getItemAtPosition(float mouseY) const {
    float listBottom = centerY - height / 2.0f;
    float listTop    = centerY + height / 2.0f;
    

    if (mouseY < listBottom || mouseY > listTop) {
        return -1;
    }

    float distanceFromTop = (listTop - mouseY) + scrollOffset;

    int index = static_cast<int>(distanceFromTop / itemHeight);

    if (index < 0 || index >= static_cast<int>(items.size())) {
        return -1;
    }
    
    return index;
}

void UIList::scrollToItem(size_t index) {
    if (index >= items.size()) return;
    
    float itemCenterY = getItemCenterY(index);
    float itemTop = itemCenterY + itemHeight / 2;
    float itemBottom = itemCenterY - itemHeight / 2;
    float listBottom = centerY - height / 2;
    float listTop = centerY + height / 2;
    
    if (itemTop > listTop) {
        scrollOffset = listTop - (index * itemHeight) - itemHeight;
    } else if (itemBottom < listBottom) {
        scrollOffset = (listTop - listBottom) - (listTop - itemBottom);
    }
    
    scrollOffset = std::clamp(scrollOffset, 0.0f, maxScroll);
}

UICollapsibleList::UICollapsibleList(uint16_t x, uint16_t y, uint16_t width, const std::string& title, uint16_t itemHeight)
    
    : UIWidget(x, y + headerHeight/2, width, itemHeight), 
      title(title), selectedText("Не выбрано"), headerHeight(40), itemHeight(itemHeight) {
    
    targetHeight = headerHeight;
    currentHeight = headerHeight;
}

void UICollapsibleList::update(float dt) {
    float speed = 10.0f;
    currentHeight += (targetHeight - currentHeight) * speed * dt;
    height = currentHeight; 

    if (expanded) {
        updateScrollRange();
        scrollOffset = std::clamp(scrollOffset, 0.0f, maxScroll);
    }
}

void UICollapsibleList::draw(Renderer& r, TextRenderer& tr) {
    if (!isVisible) return;

    float topY = centerY + headerHeight / 2.0f; 
    
    float listLeft   = centerX - width / 2.0f;
    float listRight  = centerX + width / 2.0f;
    
    float headerBottom = topY - headerHeight;
    float listBottom   = topY - currentHeight; 

    glm::vec4 headerColor = expanded ? glm::vec4(0.25f, 0.35f, 0.55f, 1.0f) 
                                     : glm::vec4(0.2f, 0.25f, 0.35f, 1.0f);
    
    float headerCenterY = topY - headerHeight / 2.0f;
    r.draw({listLeft, headerBottom}, {width, headerHeight}, headerColor);

    float arrowX = listRight - 25.0f;
    float arrowY = headerCenterY;
    r.draw({arrowX, arrowY}, {8.0f, 8.0f}, {1.0f, 1.0f, 1.0f, 1.0f});
    r.end();


    float titleX = listLeft + 15.0f;
    float titleY = headerBottom + (headerHeight * 0.35f); 
    
    std::string headerText;
    glm::vec3 textColor;
    
    if (expanded) {
        headerText = title;
        textColor = {1.0f, 1.0f, 1.0f};
    } else {
        headerText = title + ": " + selectedText;
        textColor = {0.8f, 0.9f, 1.0f};
    }
    
    tr.drawText(headerText, titleX, titleY, 1.0f, textColor);
    tr.textFlush();


    if (expanded && currentHeight > headerHeight + 1.0f) {
        float contentTop = headerBottom;
        float contentBottom = listBottom;
        float contentHeight = currentHeight - headerHeight;
        

        int fbW, fbH, winW, winH;
        glfwGetFramebufferSize(glfwGetCurrentContext(), &fbW, &fbH);
        glfwGetWindowSize(glfwGetCurrentContext(), &winW, &winH);
        
        float scaleX = (float)fbW / winW;
        float scaleY = (float)fbH / winH;
        
        glEnable(GL_SCISSOR_TEST);
        glScissor((int)(listLeft * scaleX), (int)(contentBottom * scaleY), 
                  (int)(width * scaleX), (int)(contentHeight * scaleY));

        float contentWidth = width;
        if (maxScroll > 0.001f) {
            contentWidth -= scrollbarWidth;
        }

        for (size_t i = 0; i < items.size(); ++i) {
            float itemTopY    = contentTop - (i * itemHeight) + scrollOffset;
            float itemBottomY = itemTopY - itemHeight;
            
            if (itemTopY < contentBottom || itemBottomY > contentTop) continue;

            glm::vec4 bgColor;
            if (static_cast<int>(i) == selectedIndex) {
                bgColor = {0.2f, 0.4f, 0.7f, 1.0f};
            } else if (static_cast<int>(i) == hoveredItem) {
                bgColor = {0.25f, 0.25f, 0.35f, 1.0f};
            } else {
                bgColor = (i % 2 == 0) ? glm::vec4(0.12f, 0.12f, 0.18f, 1.0f) 
                                       : glm::vec4(0.15f, 0.15f, 0.20f, 1.0f);
            }

            r.draw({listLeft, itemBottomY}, {contentWidth, itemHeight}, bgColor);
            r.end();

            float textX = listLeft + 15.0f;
            float baselineY = itemTopY - (itemHeight * 0.65f);
            
            tr.drawText(items[i], textX, baselineY, 1.0f, {0.9f, 0.9f, 0.9f});
            tr.textFlush();
        }

        glDisable(GL_SCISSOR_TEST);


        if (maxScroll > 0.001f) {
            float thumbHeight = std::max(20.0f, contentHeight * (contentHeight / (items.size() * itemHeight)));
            thumbHeight = std::min(thumbHeight, contentHeight - 2.0f);

            float scrollRatio = scrollOffset / maxScroll;

            float thumbTopY = contentTop - scrollRatio * (contentHeight - thumbHeight);
            float thumbBottom = thumbTopY - thumbHeight;
            float scrollbarX = listRight - scrollbarWidth;

            r.draw({scrollbarX, contentBottom}, {scrollbarWidth, contentHeight}, {0.1f, 0.1f, 0.15f, 1.0f});
            
            
            r.draw({scrollbarX, thumbBottom}, {scrollbarWidth, thumbHeight}, {0.4f, 0.4f, 0.5f, 1.0f});
            r.end();
        }
    }
}

bool UICollapsibleList::onEvent(EventSystem& events) {
    if (!isVisible || !isEnable) return false;

    int winH;
    glfwGetWindowSize(glfwGetCurrentContext(), nullptr, &winH);
    float mouseX = events.getMouseX();
    float mouseY = events.getMouseY();

    float topY = centerY + headerHeight / 2.0f; 
    
    float listLeft   = centerX - width / 2.0f;
    float listRight  = centerX + width / 2.0f;
    
    float headerBottom = topY - headerHeight;
    float listBottom   = topY - currentHeight;

    bool inside = (mouseX >= listLeft && mouseX <= listRight && 
                   mouseY <= topY && mouseY >= listBottom);
    
    if (!inside) {
        hoveredItem = -1;
        return false;
    }

    bool handled = false;

    if (events.isButtonClicked(GLFW_MOUSE_BUTTON_LEFT)) {
 
        if (mouseY <= topY && mouseY >= headerBottom) {
            toggle();
            return true;
        }


        if (expanded && mouseY < headerBottom) {
            int clickedIndex = getItemAtPosition(mouseY, topY, headerBottom);
            if (clickedIndex >= 0 && static_cast<size_t>(clickedIndex) < items.size()) {
                setSelectedItem(clickedIndex);
                hoveredItem = clickedIndex;
                if (onItemClicked) onItemClicked(clickedIndex);
                handled = true;
            }
        }
    }

    if (expanded && mouseY < headerBottom) {
        float scrollY = events.getScrollY();
        if (scrollY != 0.0f) {
            scrollOffset -= scrollY * 30.0f;
            scrollOffset = std::clamp(scrollOffset, 0.0f, maxScroll);
            handled = true;
        }
    }

    if (expanded && !handled && mouseY < headerBottom) {
        hoveredItem = getItemAtPosition(mouseY, topY, headerBottom);
    }

    return handled;
}

int UICollapsibleList::getItemAtPosition(float mouseY, float topY, float headerBottom) const {
    if (mouseY > headerBottom || mouseY < topY - currentHeight) {
        return -1;
    }
    
    float distFromContentTop =  -mouseY + headerBottom + scrollOffset;
    int index = static_cast<int>(distFromContentTop / itemHeight);
    
    return (index >= 0 && index < static_cast<int>(items.size())) ? index : -1;
}

void UICollapsibleList::addItem(const std::string& text) {
    items.push_back(text);
    if (expanded) updateScrollRange();
}

void UICollapsibleList::clearItems() {
    items.clear();
    scrollOffset = 0.0f;
    maxScroll = 0.0f;
    selectedIndex = -1;
    hoveredItem = -1;
    selectedText = "Не выбрано";
}

void UICollapsibleList::setSelectedItem(int index) {
    if (index >= 0 && index < static_cast<int>(items.size())) {
        selectedIndex = index;
        selectedText = items[index];
    } else {
        selectedIndex = -1;
        selectedText = "Не выбрано";
    }
}

void UICollapsibleList::setExpanded(bool exp) {
    expanded = exp;
    targetHeight = expanded ? std::min(getContentHeight(), maxVisibleItems * itemHeight) + headerHeight 
                            : headerHeight;
}

void UICollapsibleList::toggle() {
    setExpanded(!expanded);
}

void UICollapsibleList::setOnItemClicked(std::function<void(int)> callback) {
    onItemClicked = std::move(callback);
}

float UICollapsibleList::getContentHeight() const {
    return items.size() * itemHeight;
}

void UICollapsibleList::updateScrollRange() {
    float contentHeight = items.size() * itemHeight;
    float visibleHeight = currentHeight - headerHeight;
    maxScroll = std::max(0.0f, contentHeight - visibleHeight);
}
