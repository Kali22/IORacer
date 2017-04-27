#pragma once
//
// Created by pawel on 12.04.17.
//
#include <Button.h>
#include <ButtonState.h>
#include <ButtonStateType.h>

#define BUTTON_TIME_TO_UPDATE_SLOW 400
#define BUTTON_TIME_TO_UPDATE_FAST 50
#define BUTTON_TIME_TO_SPEED_UP 1200

class ButtonManager {
public:
    ButtonManager(std::vector<ButtonPtr> buttons);

    /**
     * Process events connected with clicking on buttons. Process released
     * mouse event or mouse pressed.
     */
    void ProcessEvent(const sf::Event &event, const sf::Vector2f &mousePos);

    /**
     * If button has been pressed and time from last click is big enough, call
     * OnClick method.
     */
    void ManageClicks();

    /**
     * If any button hasn't been pressed toggle hover on buttons.
     */
    void ManageHover(const sf::Vector2f &mousePos);

    /**
     * We should release buttons on exiting from menu.
     */
    void ReleaseButton();

private:
    std::vector<ButtonPtr> buttons_;
    const int timeToUpdateSlowMsc_ = BUTTON_TIME_TO_UPDATE_SLOW;
    const int timeToUpdateFastMsc_ = BUTTON_TIME_TO_UPDATE_FAST;
    const int timeToSpeedUpMsc_ = BUTTON_TIME_TO_SPEED_UP;
    ButtonStatePtr buttonState_;
};

using ButtonManagerPtr = std::shared_ptr<ButtonManager>;

