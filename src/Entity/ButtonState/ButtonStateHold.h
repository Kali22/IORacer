#pragma once
//
// Created by pawel on 12.04.17.
//

#include <SFML/Graphics.hpp>
#include <ButtonState.h>
#include <Button.h>
#include <ButtonStateType.h>
#include <utility>

typedef enum {
    SLOW,
    FAST,
} ButtonSpeed;

/// Shared from this http://stackoverflow.com/questions/11711034/stdshared-ptr-of-this
/// http://en.cppreference.com/w/cpp/memory/enable_shared_from_this
class ButtonStateHold : public ButtonState,
                        public std::enable_shared_from_this<ButtonStateHold> {
public:
    ButtonStateHold(ButtonPtr pressedButton, int timeToUpdateSlowMsc,
                    int timeToUpdateFastMsc, int timeToSpeedUpMsc);

    virtual ButtonStatePtr ManageClicks();

    virtual ButtonStateType GetType() const;

private:
    ButtonPtr pressedButton_;
    const int timeToUpdateSlowMsc_;
    const int timeToUpdateFastMsc_;
    const int timeToSpeedUpMsc_;
    sf::Clock timeHold_;
    sf::Clock timeHoldUpdate_;
    ButtonSpeed buttonSpeed_;
};


