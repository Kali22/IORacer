#pragma once
//
// Created by pawel on 12.04.17.
//

#include <SFML/Graphics.hpp>
#include <utility>
#include <bits/stdc++.h>
#include <ButtonStateType.h>

class ButtonState;

using ButtonStatePtr = std::shared_ptr<ButtonState>;

class ButtonState {
public:
    virtual ButtonStatePtr ManageClicks() = 0;

    virtual ButtonStateType GetType() const = 0;
};

