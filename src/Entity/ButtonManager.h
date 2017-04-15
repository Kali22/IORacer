#pragma once
//
// Created by pawel on 12.04.17.
//
#include <Button.h>
#include <ButtonState.h>
#include <ButtonStateType.h>

class ButtonManager {
public:
    ButtonManager(std::vector<ButtonPtr> buttons, int timeToUpdateSlowMsc,
                  int timeToUpdateFastMsc, int timeToSpeedUpMsc);

    /**
     * Process events connected with clicking on buttons. Process released
     * mouse event or mouse pressed.
     */
    void ProcessEvent(const sf::Event& event, const sf::Vector2f& mousePos);

    /**
     * If button has been pressed and time from last click is big enough, call
     * OnClick method.
     */
    void ManageClicks();

    /**
     * If any button hasn't been pressed toggle hover on buttons.
     */
    void ManageHover(const sf::Vector2f& mousePos);

    /**
     * We should release buttons on exiting from menu.
     */
    void ReleaseButton();
private:
    std::vector<ButtonPtr> buttons_;
    const int timeToUpdateSlowMsc_;
    const int timeToUpdateFastMsc_;
    const int timeToSpeedUpMsc_;
    ButtonStatePtr buttonState_;
};

using ButtonManagerPtr = std::shared_ptr<ButtonManager>;

