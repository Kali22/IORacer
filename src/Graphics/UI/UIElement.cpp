#include "UIElement.h"
#include <ActivityManager.h>
#include <Activity.h>

UIElement::UIElement(int id, std::string name, ActivityPtr activity)
        : name_(name),
          id_(id),
          activity_(activity),
          size_(sf::FloatRect(0.5, 0.5, 1, 1)),
          hover_(false) {

}

UIElement::UIElement(int id, std::string name, sf::FloatRect size, ActivityPtr activity)
        : name_(name),
          id_(id),
          activity_(activity),
          size_(size),
          hover_(false) {
}

void UIElement::EventAction(sf::Event event) {
    if (event.type == sf::Event::MouseMoved) {
        if (!hover_ && bounds_.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
            hover_ = true;
            activity_->EventAction(Event(UIEvent(UI_EVENT_MOUSE_OVER, id_)));
        }

        if (hover_ && !bounds_.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
            hover_ = false;
            activity_->EventAction(Event(UIEvent(UI_EVENT_MOUSE_LOST, id_)));
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (bounds_.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            activity_->EventAction(Event(UIEvent(UI_EVENT_CLICK, id_)));
        }
    }

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
    TexturePtr texture = activity_->GetActivityManager()->GetTextureManager()->GetTextureByName(name);
    if (texture == nullptr) {
        fprintf(stderr, "UIElement: No such texture named %s!\n", name.c_str());
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
