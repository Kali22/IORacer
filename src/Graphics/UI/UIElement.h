#pragma once


#include <bits/stdc++.h>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <ActivityCommon.h>
#include <GraphicsCommon.h>

class UIElement;

using UIElementPtr = std::shared_ptr<UIElement>;

class UIElement : public std::enable_shared_from_this<UIElement> {
public:
    /** Invoke event responsible UI. Default size: full screen */
    UIElement(int id, std::string name_, ActivityPtr activity);

    /** Invoke event responsible UI with given size. */
    UIElement(int id, std::string name_, sf::FloatRect size, ActivityPtr activity);

    void EventAction(sf::Event event);

    std::string GetName() const;

    int GetId() const;

    virtual void Render(RenderWindowPtr window);

    sf::FloatRect GetRelativeSize() const;

    void SetAbsoluteSize(sf::FloatRect size);

    void SetBackgroundTexture(std::string name);

    void SetBackgroundColor(sf::Color color);

    void SetOutlineColor(sf::Color color);

    void SetOutlineThickness(float thickness);

protected:
    std::string name_;
    int id_;
    bool hover_;

    sf::FloatRect size_; //!< Relative dimension
    sf::RectangleShape bounds_; //!< Graphics
    ActivityPtr activity_; //!< Activity handler
};
