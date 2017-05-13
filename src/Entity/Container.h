//
// Created by jacek on 20.04.17.
//
#pragma once

#include <Movable.h>
#include <Updatable.h>
#include <Drawable.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/**
 * Container for graphics.
 * @TODO auto space arrangement?
 */
class Container : public Movable, public Updatable, public Drawable {
public:
    Container(sf::FloatRect rect);

    void Draw(RenderWindowPtr window) const;

    void Update();

    void SetPosition(const sf::Vector2f &pos);

    void SetPosition(float x, float y);

    void Move(const sf::Vector2f &dr);

    void Move(float dx, float dy);

    void AddMovable(MovablePtr movablePtr);

    void AddUpdatable(UpdatablePtr updatablePtr);

    void FrameOn();

    void FrameOff();

    void Show();

    void Hide();

    sf::FloatRect GetGridElement(int cols, int rows, int colEl, int rowEl, float padding);

    sf::Vector2f GetSize() const;

private:
    bool visible_;
    bool frame_;
    sf::RectangleShape rect_;
    std::vector<MovablePtr> list_;
    std::vector<UpdatablePtr> updatableList_;
};

using ContainerPtr = std::shared_ptr<Container>;