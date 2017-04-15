//
// Created by pawel on 12.04.17.
//

#include <ButtonState.h>
#include <Button.h>
#include <utility>
#include <ButtonStateHold.h>

ButtonStateHold::ButtonStateHold(ButtonPtr pressedButton,
                                 int timeToUpdateSlowMsc,
                                 int timeToUpdateFastMsc,
                                 int timeToSpeedUpMsc)
        : pressedButton_(pressedButton),
          timeToUpdateSlowMsc_(timeToUpdateSlowMsc),
          timeToUpdateFastMsc_(timeToUpdateFastMsc),
          timeToSpeedUpMsc_(timeToSpeedUpMsc),
          buttonSpeed_(SLOW) {
    /// We call OnClick in constructor to perform first click immediately on
    /// button click.
    if (pressedButton_ != nullptr) {
        pressedButton->OnClick();
    }
}

ButtonStateType ButtonStateHold::GetType() const {
    return HOLD;
}

ButtonStatePtr ButtonStateHold::ManageClicks() {
    if (pressedButton_ == nullptr) {
        return shared_from_this();
    }

    if (timeHold_.getElapsedTime().asMilliseconds() >
        timeToSpeedUpMsc_) { /// Change mode to FAST
        buttonSpeed_ = FAST;
    }

    int timeToUpdateMsc = timeToUpdateSlowMsc_;
    if (buttonSpeed_ == FAST) {
        timeToUpdateMsc = timeToUpdateFastMsc_;
    }

    if (timeHoldUpdate_.getElapsedTime().asMilliseconds() >
        timeToUpdateMsc) {
        pressedButton_->OnClick();
        timeHoldUpdate_.restart();
    }
    return shared_from_this();
}
