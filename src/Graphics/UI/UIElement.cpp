#include <UIElement.h>
#include <ActivityManager.h>

UIElement::UIElement(int id, std::string name, WeakActivityPtr activity) :
        name_(name),
        id_(id),
        activity_(activity),
        size_(centeredFullScreen),
        hover_(false) {}

UIElement::UIElement(int id, std::string name, sf::FloatRect size,
                     WeakActivityPtr activity) :
        name_(name),
        id_(id),
        activity_(activity),
        size_(size),
        hover_(false) {}

void UIElement::EventAction(sf::Event event) {
    HandleMouseMoved(event);

    if (event.type == sf::Event::MouseButtonPressed) {
        if (bounds_.getGlobalBounds().contains(event.mouseButton.x,
                                               event.mouseButton.y)) {
            activity_.lock()->EventAction(Event(UI_EVENT_CLICK, name_));
        }
    }

}

void UIElement::HandleMouseMoved(sf::Event event) {
    if (event.type != sf::Event::MouseMoved) {
        return;
    }
    bool nowHovered = bounds_.getGlobalBounds().contains(event.mouseMove.x,
                                                         event.mouseMove.y);
    if (!hover_ && nowHovered) {
        activity_.lock()->EventAction(Event(UI_EVENT_MOUSE_OVER, name_));
    } else if (hover_ && !nowHovered) {
        activity_.lock()->EventAction(Event(UI_EVENT_MOUSE_LOST, name_));
    }
    hover_ = nowHovered;
}

std::string UIElement::GetName() const {
    return name_;
}

void UIElement::Render(RenderWindowPtr window) {
    window->draw(bounds_);
}

sf::FloatRect UIElement::GetRelativeSize() const {
    return size_;
}

void UIElement::SetAbsoluteSize(sf::FloatRect size) {
    bounds_.setSize(sf::Vector2f(size.width, size.height));
    bounds_.setOrigin(0.5f * size.width, 0.5f * size.height);
    bounds_.setPosition(size.left, size.top);
}


void UIElement::SetBackgroundTexture(std::string name) {
    TexturePtr texture = activity_.lock()->GetActivityManager().lock()->GetTextureManager()->GetTextureByName(name);
    if (texture == nullptr) {
        std::cerr << "UIElement: No such texture named "
                  << name.c_str() << std::endl;
        exit(1);
    }
    bounds_.setTexture(texture->GetTexture());
}

void UIElement::SetBackgroundColor(sf::Color color) {
    bounds_.setFillColor(color);
}

void UIElement::SetOutlineColor(sf::Color color) {
    bounds_.setOutlineColor(color);
}

void UIElement::SetOutlineThickness(float thickness) {
    bounds_.setOutlineThickness(thickness);
}

int UIElement::GetId() const {
    return id_;
}
