#include <Text.h>
#include <map>
#include <string>

std::map<std::string, std::string> font{
        {"andale_mono", "../resource/fonts/Andale_Mono.ttf"},
        {"calibrib",    "../resource/fonts/calibrib.ttf"},
        {"calibrii",    "../resource/fonts/calibrii.ttf"},
        {"calibri",     "../resource/fonts/calibri.ttf"},
        {"calibriz",    "../resource/fonts/calibriz.ttf"},
        {"cambriab",    "../resource/fonts/cambriab.ttf"},
        {"cambriai",    "../resource/fonts/cambriai.ttf"},
        {"cambriaz",    "../resource/fonts/cambriaz.ttf"},
        {"candarab",    "../resource/fonts/candarab.ttf"},
        {"candarai",    "../resource/fonts/candarai.ttf"},
        {"candara",     "../resource/fonts/candara.ttf"},
        {"candaraz",    "../resource/fonts/candaraz.ttf"},
        {"consolab",    "../resource/fonts/consolab.ttf"},
        {"consolai",    "../resource/fonts/consolai.ttf"},
        {"consolaz",    "../resource/fonts/consolaz.ttf"},
        {"constanb",    "../resource/fonts/constanb.ttf"},
        {"constani",    "../resource/fonts/constani.ttf"},
        {"constan",     "../resource/fonts/constan.ttf"},
        {"constanz",    "../resource/fonts/constanz.ttf"},
        {"corbelb",     "../resource/fonts/corbelb.ttf"},
        {"corbeli",     "../resource/fonts/corbeli.ttf"},
        {"corbel",      "../resource/fonts/corbel.ttf"},
        {"impact",      "../resource/fonts/impact.ttf"}
};

Text::Text(std::string text, std::string fontName, sf::Vector2f position,
           float size) {
    textPosition_ = TEXT_CENTER;
    frame_ = false;
    CreateText(text, fontName, size);
    rectangleFrame_.setOrigin(0, 0);
    rectangleFrame_.setSize(sf::Vector2f(0.f, 0.f));
    rectangleFrame_.setPosition(position.x, position.y);
    SetDefaultFrameStyle();
    sideMargin_ = 0.f;
    JustifyText();
}

Text::Text(std::string text, std::string fontName, sf::FloatRect frame, float size, TextJustification position) {
    CreateText(text, fontName, size);
    frame_ = false;
    textPosition_ = position;
    SetDefaultFrameStyle();
    SetDefaultMargin();
    SetTextFrame(frame);
    JustifyText();
}

void Text::Draw(RenderWindowPtr window) const {
}

void Text::SetText(std::string txt) {
    sfText_.setString(txt);
    sf::FloatRect rect = sfText_.getLocalBounds();
    sfText_.setOrigin(rect.left, rect.top);
    JustifyText();
}

void Text::SetColor(sf::Color color) {
    sfText_.setColor(color);
}

void Text::CreateText(std::string text, std::string fontName, float size) {
    if (!sfFont_.loadFromFile(font[fontName])) {
        throw std::runtime_error("Font loading failed");
    }
    sfText_.setFont(sfFont_);
    sfText_.setCharacterSize((unsigned int) size);
    sfText_.setString(text);
    sfText_.setColor(sf::Color::White);
    sf::FloatRect rect = sfText_.getLocalBounds();
    sfText_.setOrigin(rect.left, rect.top);
}

void Text::JustifyText() {
    auto position = rectangleFrame_.getPosition();
    auto size = rectangleFrame_.getSize();
    auto rect = sfText_.getLocalBounds();
    float width = rect.width;
    float height = rect.height;
    float textPositionY;
    float textPositionX;

    if (textPosition_ == TEXT_CENTER) {
        textPositionY = position.y + size.y / 2.f - height / 2.f;
        textPositionX = position.x + size.x / 2.f - width / 2.f;
    } else if (textPosition_ == TEXT_RIGHT) {
        textPositionY = position.y + size.y / 2.f - height / 2.f;
        textPositionX = position.x + size.x - width - sideMargin_;
    } else {
        textPositionY = position.y + size.y / 2.f - height / 2.f;
        textPositionX = position.x + sideMargin_;
    }
    sfText_.setPosition(textPositionX, textPositionY);
}

void Text::FrameOn() {
    frame_ = true;
}

void Text::FrameOff() {
    frame_ = false;
}

void Text::SetTextFrame(sf::FloatRect frame) {
    rectangleFrame_.setOrigin(0, 0);
    rectangleFrame_.setSize(sf::Vector2f(frame.width, frame.height));
    rectangleFrame_.setPosition(frame.left, frame.top);
    JustifyText();
}

void Text::SetDefaultFrameStyle() {
    rectangleFrame_.setFillColor(sf::Color(30, 30, 30, 50));
    rectangleFrame_.setOutlineColor(sf::Color(200, 200, 200, 80));
    rectangleFrame_.setOutlineThickness(0.f);
}

void Text::SetDefaultMargin() {
    sideMargin_ = 5.f;
}

void Text::SetFrameColor(sf::Color color) {
    rectangleFrame_.setOutlineColor(color);
}

void Text::SetFrameFillColor(sf::Color color) {
    rectangleFrame_.setFillColor(color);
}

void Text::SetFrameThickness(float thickness) {
    rectangleFrame_.setOutlineThickness(thickness);
}

sf::FloatRect Text::GetSameFrameBelow(float margin) {
    sf::FloatRect rect = rectangleFrame_.getGlobalBounds();
    rect.top += rect.height + margin;
    return rect;
}

sf::FloatRect Text::GetSameFrameAbove(float margin) {
    sf::FloatRect rect = rectangleFrame_.getGlobalBounds();
    rect.top -= rect.height + margin;
    return rect;
}

sf::FloatRect Text::GetSameFrameLeft(float margin) {
    sf::FloatRect rect = rectangleFrame_.getGlobalBounds();
    rect.left -= rect.width + margin;
    return rect;
}

sf::FloatRect Text::GetSameFrameRight(float margin) {
    sf::FloatRect rect = rectangleFrame_.getGlobalBounds();
    rect.left += rect.width + margin;
    return rect;
}

void Text::SetPosition(const sf::Vector2f &pos) {
    rectangleFrame_.setPosition(pos);
    JustifyText();
}

void Text::SetPosition(float x, float y) {
    rectangleFrame_.setPosition(x, y);
    JustifyText();
}

void Text::Move(const sf::Vector2f &dr) {
    rectangleFrame_.move(dr);
    JustifyText();
}

void Text::Move(float dx, float dy) {
    rectangleFrame_.move(dx, dy);
    JustifyText();
}
