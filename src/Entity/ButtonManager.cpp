//
// Created by pawel on 12.04.17.
//
#include <Button.h>
#include <ButtonManager.h>
#include <ButtonStateReleased.h>
#include <ButtonStateHold.h>

ButtonManager::ButtonManager(std::vector<ButtonPtr> buttons)
        : buttons_(buttons),
          buttonState_(std::make_shared<ButtonStateReleased>()) {
}

void ButtonManager::ProcessEvent(const sf::Event &event,
                                 const sf::Vector2f &mousePos) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        ButtonPtr pressedButton = nullptr;
        for (const auto &button : buttons_) {
            if (button->ToggleHover(mousePos)) {
                pressedButton = button;
            }
        }
        buttonState_ =
                std::make_shared<ButtonStateHold>(pressedButton,
                                                  timeToUpdateSlowMsc_,
                                                  timeToUpdateFastMsc_,
                                                  timeToSpeedUpMsc_);
    } else if (event.type == sf::Event::MouseButtonReleased &&
               event.mouseButton.button == sf::Mouse::Left) {
        buttonState_ = std::make_shared<ButtonStateReleased>();
    }
}

void ButtonManager::ManageClicks() {
    buttonState_ = buttonState_->ManageClicks();
}

void ButtonManager::ManageHover(const sf::Vector2f &mousePos) {
    if (buttonState_->GetType() == RELEASED) {
        for (auto &button : buttons_) {
            button->ToggleHover(mousePos);
        }
    }
}

void ButtonManager::ReleaseButton() {
    buttonState_ = std::make_shared<ButtonStateReleased>();
}
