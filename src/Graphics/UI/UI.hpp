#pragma once
#include<functional>
#include<vector>
#include<string>
#include"Renderer.hpp"
#include"TextRenderer.hpp"
#include"EventSystem.hpp"

class UIWidget{
    protected:
    uint16_t centerX = 0;
    uint16_t centerY = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    public:

    bool isVisible = false;
    bool isEnable = false;

    UIWidget(uint16_t posX, uint16_t posY, uint16_t width, uint16_t height):
    centerX(posX), centerY(posY), width(width), height(height), isVisible(true), isEnable(true) {}

    virtual ~UIWidget() = default;

    virtual void draw(Renderer& render, TextRenderer& textRender) = 0;
    virtual void update(float) = 0;
    virtual bool onEvent(EventSystem& events) { return false; }
    
    bool contains(float mouseX, float mouseY){
        return (centerX - width / 2) <= mouseX && (centerY - height / 2) <= mouseY &&
        (centerX + width / 2) >= mouseX && (centerY + height / 2) >= mouseY;
    }

    void setPosition(uint16_t newX, uint16_t newY){ centerX = newX; centerY = newY; }
    void setSize(uint16_t newX, uint16_t newY){width = newX; height = newY; }
    void setEnable(bool e){ isEnable = e; }
    void setVisiable(bool v) {isVisible = v; }



};

class UIButton : protected UIWidget {
    private:
    std::string text;
    glm::vec4 backgroundColor;
    glm::vec3 textColor;
    std::function<void(int)> onClicked;
    bool isClicked = false;

    public:
    UIButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, glm::vec4 backColor, const std::string& text, glm::vec3 textColor);
    ~UIButton();
    void draw (Renderer& render, TextRenderer& textRender) override;
    bool onEvent(EventSystem& events) override;
    void update(float) override;

    void setOnClicked(std::function<void(int)> callback);

    bool isHovered;
    bool isPressed;
};

class UIText: protected UIWidget{
    private:

    std::string text;
    glm::vec3 color;
    float fontSize;

    public:
    UIText(float x, float y, const std::string& text, 
           glm::vec3 color = {1,1,1}, float fontSize = 20.0f)
        : UIWidget(x, y, 0, fontSize), text(text), color(color), fontSize(fontSize) {
    }

    void draw(Renderer& r, TextRenderer& tr) override;
    void setText(const std::string& t);
    const std::string& getText() const;
    void setFontSize(float s);
};


class UIInputText : protected UIWidget {
    private:

    std::u32string text;
    std::string placeholder;
    std::u32string placeholderUnicode;

    float fontSize;
    bool focused = false;
    int cursorPos = 0;
    bool showCursor = true;
    float cursorBlinkTimer = 0.0f;
    glm::vec3 textColor = {1,1,1};

    public:

    UIInputText(float x, float y, float w, float h, 
                const std::string& placeholder = "", float fontSize = 20.0f);

    void update(float dt);
    void draw(Renderer& r, TextRenderer& tr) override;

    bool onEvent(EventSystem& events) override;

    void setText(const std::string& t) { text = TextRenderer::charToUnicode(t); cursorPos = text.length(); }
    const std::u32string& getText() const { return text; }
    void setFocused(bool f) { focused = f; }
};

class UIList : public UIWidget {

    private:
    std::vector<std::u32string> items;
    float itemHeight;
    float scrollOffset = 0.0f;
    float maxScroll = 0.0f;
    float scrollbarWidth = 10.0f;
    bool showScrollbar = true;
    
    int hoveredItem = -1;
    int selectedIndex = -1;
    
    std::function<void(int)> onItemClicked;

    void updateScrollRange();
    float getItemCenterY(size_t index) const;
    int getItemAtPosition(float mouseY) const;
    void scrollToItem(size_t index);

    public:
    UIList(float x, float y, float w, float h, float itemHeight = 40.0f);
    ~UIList() override = default;

    void update(float dt) override;
    void draw(Renderer& r, TextRenderer& tr) override;
    bool onEvent(EventSystem& events) override;

    void addItem(const std::string& text);
    void addItems(const std::vector<std::string>& items);
    void removeItem(size_t index);
    void clearItems();

    size_t getItemCount() const { return items.size(); }
    const std::u32string& getItemText(size_t index) const;
    int getSelectedIndex() const { return selectedIndex; }
    
    void setOnItemClicked(std::function<void(int)> callback);
    

    void setItemHeight(float h) { itemHeight = h; }
    float getItemHeight() const { return itemHeight; }
    void setShowScrollbar(bool show) { showScrollbar = show; }
};

class UICollapsibleList : public UIWidget {
    private:
    std::string title;
    std::string selectedText;
    std::vector<std::string> items;
    
    float headerHeight;
    float itemHeight;
    int maxVisibleItems = 5;
    
    bool expanded = false;
    float currentHeight = 0.0f;
    float targetHeight = 0.0f;
    
    float scrollOffset = 0.0f;
    float maxScroll = 0.0f;
    float scrollbarWidth = 10.0f;
    
    int hoveredItem = -1;
    int selectedIndex = -1;
    
    std::function<void(int)> onItemClicked;
    
    float getContentHeight() const;
    void updateScrollRange();
    int getItemAtPosition(float mouseY, float topY, float headerBottom) const;

    public:

    UICollapsibleList(uint16_t x, uint16_t y, uint16_t width, const std::string& title, uint16_t itemHeight = 40.0f);
    ~UICollapsibleList() override = default;

    void update(float dt) override;
    void draw(Renderer& r, TextRenderer& tr) override;
    bool onEvent(EventSystem& events) override;

    void addItem(const std::string& text);
    void clearItems();
    
    void setSelectedItem(int index);
    int getSelectedItem() const { return selectedIndex; }
    const std::string& getSelectedItemText() const { return selectedText; }

    void setExpanded(bool expanded);
    bool isExpanded() const { return expanded; }
    void toggle();
    
    void setOnItemClicked(std::function<void(int)> callback);

    void setHeaderHeight(float h) { headerHeight = h; }
    void setItemHeight(float h) { itemHeight = h; }
    void setMaxVisibleItems(int n) { maxVisibleItems = n; }

};


