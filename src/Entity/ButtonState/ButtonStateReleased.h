#pragma once
//
// Created by pawel on 12.04.17.
//

#include <ButtonState.h>
#include <SFML/Graphics.hpp>
#include <ButtonStateType.h>

/// Shared from this http://stackoverflow.com/questions/11711034/stdshared-ptr-of-this
/// http://en.cppreference.com/w/cpp/memory/enable_shared_from_this
class ButtonStateReleased : public ButtonState,
                            public std::enable_shared_from_this<ButtonStateReleased> {
public:
    ButtonStateReleased();

    virtual ButtonStatePtr ManageClicks();

    virtual ButtonStateType GetType() const;
};


