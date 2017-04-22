//
// Created by jacek on 20.04.17.
//
#pragma once

#include <Entity/Movable.h>
#include <Entity/Updatable.h>

class Container : public Movable, public Updatable {
public:
    Container(sf::FloatRect rect);

    void Draw(sf::RenderWindow *window) const;

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

private:
    bool visible_;
    bool frame_;
    sf::RectangleShape rect_;
    std::vector<MovablePtr> list_;
    std::vector<UpdatablePtr> updatableList_;
};

using ContainerPtr = std::shared_ptr<Container>;