#include "Workshop.h"

/*
void Workshop::addButton(const sf::Vector2f &position,
                         const sf::Vector2f &button_size, std::string text,
                         std::function<void(sf::RenderWindow *window_)> func) {
    registerButton(std::make_shared<RedirectButton>(position, button_size, text, func));
}*/

Workshop::Workshop(sf::RenderWindow *window, RacePtr race) :
        Module(window), race_(race), carParams_(race_->getVehicle()->getCarParameters()) {

    const sf::Vector2f gameButtonSize = sf::Vector2f(400, 80);
    const sf::Vector2f statsButtonSize = sf::Vector2f(50, 50);
    const sf::Vector2f textFieldSize = sf::Vector2f(200, 60);
    const float textSize = 50;

    returnButton_ = std::make_shared<Button>(
            sf::Vector2f(400, 520),
            gameButtonSize,
            "Return to menu",
            [this]() {
                close_ = true;
            });
    registerButton(returnButton_);


    std::string plus = "+";
    std::string minus = "-";
    maxSpeedText_ = std::make_shared<Text>(
            std::to_string((int) carParams_->maxForwardSpeed), "impact",
            sf::Vector2f(400, 100), textSize);
    objects_.push_back(maxSpeedText_);

    minusMaxSpeed_ = std::make_shared<Button>(
            sf::Vector2f(250, 100),
            statsButtonSize,
            minus,
            [this]() {
                carParams_->maxForwardSpeed--;
                maxSpeedText_->SetText(std::to_string((int)
                                                              carParams_->maxForwardSpeed));
            });
    registerButton(minusMaxSpeed_);

    plusMaxSpeed_ = std::make_shared<Button>(
            sf::Vector2f(550, 100),
            statsButtonSize,
            plus,
            [this]() {
                carParams_->maxForwardSpeed++;
                maxSpeedText_->SetText(std::to_string((int)
                                                              carParams_->maxForwardSpeed));
            });
    registerButton(plusMaxSpeed_);

    accelerationText_ = std::make_shared<Text>(
            std::to_string((int) carParams_->maxEnginePower), "impact",
            sf::Vector2f(400, 200), textSize);
    objects_.push_back(accelerationText_);

    minusMaxSpeed_ = std::make_shared<Button>(
            sf::Vector2f(250, 200),
            statsButtonSize,
            minus,
            [this]() {
                carParams_->maxEnginePower--;
                accelerationText_->SetText(std::to_string((int)
                                                                  carParams_->maxEnginePower));
            });
    registerButton(minusMaxSpeed_);

    plusMaxSpeed_ = std::make_shared<Button>(
            sf::Vector2f(550, 200),
            statsButtonSize,
            plus,
            [this]() {
                carParams_->maxEnginePower++;
                accelerationText_->SetText(std::to_string((int)
                                                                  carParams_->maxEnginePower));
            });
    registerButton(plusMaxSpeed_);
}

int Workshop::run() {
    close_ = false;
    while (!close_) {
        bool mouseClick = false; // info for buttons

        // EVENT handling
        sf::Event event;
        while (window_->pollEvent(event)) {
            // "close_ requested" event: end while loop
            if (event.type == sf::Event::Closed) {
                close_ = true;
            }
            // handle mouse click
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                mouseClick = true;
            }
        }

        /// BUTTON things
        std::shared_ptr<Button> activeButton = nullptr;
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window_));
        // select hovered button, change style
        for (auto &button : buttons_) {
            if (button->toggleHover(mousePos)) {
                activeButton = button;
            }
        }
        if (activeButton != nullptr && mouseClick) {
            activeButton->onClick();
        }

        // DRAWING
        window_->clear(sf::Color(60, 70, 80));
        for (auto &drawableObject : objects_) {
            drawableObject->Draw(window_);
        }
        window_->display();
    }
    return 0;
}
