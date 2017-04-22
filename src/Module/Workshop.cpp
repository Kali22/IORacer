#include "Workshop.h"

void Workshop::initMaxSpeedControl(
        const sf::Vector2f &statsButtonSize, const sf::Vector2f &labelSize, float textSize, int posX, int posY) {
    maxSpeedLabel_ = std::make_shared<Text>("Speed", "impact", sf::Vector2f(150, posY), textSize);
    objects_.push_back(maxSpeedLabel_);

    maxSpeedText_ = std::make_shared<Text>(
            std::to_string((int) carParams_->maxForwardSpeed), "impact",
            sf::Vector2f(posX, posY), textSize);
    objects_.push_back(maxSpeedText_);

    minusMaxSpeed_ = std::make_shared<Button>(
            sf::Vector2f(posX - 150, posY),
            statsButtonSize,
            "-",
            [this]() {
                carParams_->maxForwardSpeed--;
                maxSpeedText_->SetText(std::to_string((int) carParams_->maxForwardSpeed));
            });
    registerButton(minusMaxSpeed_);

    plusMaxSpeed_ = std::make_shared<Button>(
            sf::Vector2f(posX + 150, posY),
            statsButtonSize,
            "+",
            [this]() {
                carParams_->maxForwardSpeed++;
                maxSpeedText_->SetText(std::to_string((int) carParams_->maxForwardSpeed));
            });
    registerButton(plusMaxSpeed_);
}

void Workshop::initMaxEnginePowerControl(
        const sf::Vector2f &statsButtonSize, const sf::Vector2f &labelSize, float textSize, int posX, int posY) {
    maxEnginePowerLabel_ = std::make_shared<Text>("Acceleration", "impact", sf::Vector2f(150, posY), textSize);
    objects_.push_back(maxEnginePowerLabel_);

    maxEnginePowerText_ = std::make_shared<Text>(
            std::to_string((int) carParams_->maxEnginePower), "impact",
            sf::Vector2f(posX, posY), textSize);
    objects_.push_back(maxEnginePowerText_);

    minusMaxEnginePower_ = std::make_shared<Button>(
            sf::Vector2f(posX - 150, posY),
            statsButtonSize,
            "-",
            [this]() {
                carParams_->maxEnginePower--;
                maxEnginePowerText_->SetText(std::to_string((int) carParams_->maxEnginePower));
            });
    registerButton(minusMaxEnginePower_);

    plusMaxEnginePower_ = std::make_shared<Button>(
            sf::Vector2f(posX + 150, posY),
            statsButtonSize,
            "+",
            [this]() {
                carParams_->maxEnginePower++;
                maxEnginePowerText_->SetText(std::to_string((int) carParams_->maxEnginePower));
            });
    registerButton(plusMaxEnginePower_);
}

void Workshop::initSteeringSpeedControl(
        const sf::Vector2f &statsButtonSize, const sf::Vector2f &labelSize, float textSize, int posX, int posY) {
    steeringSpeedLabel_ = std::make_shared<Text>("Steering", "impact", sf::Vector2f(150, posY), textSize);
    objects_.push_back(steeringSpeedLabel_);

    steeringSpeedText_ = std::make_shared<Text>(
            std::to_string((int) carParams_->steeringSpeed), "impact",
            sf::Vector2f(posX, posY), textSize);
    objects_.push_back(steeringSpeedText_);

    minusSteeringSpeed_ = std::make_shared<Button>(
            sf::Vector2f(posX - 150, posY),
            statsButtonSize,
            "-",
            [this]() {
                carParams_->steeringSpeed--;
                steeringSpeedText_->SetText(std::to_string((int) carParams_->steeringSpeed));
            });
    registerButton(minusSteeringSpeed_);

    plusSteeringSpeed_ = std::make_shared<Button>(
            sf::Vector2f(posX + 150, posY),
            statsButtonSize,
            "+",
            [this]() {
                carParams_->steeringSpeed++;
                steeringSpeedText_->SetText(std::to_string((int) carParams_->steeringSpeed));
            });
    registerButton(plusSteeringSpeed_);
}

Workshop::Workshop(sf::RenderWindow *window, RacePtr race) :
        Module(window),
        race_(race),
        carParams_(race_->GetVehicle()->GetCarParameters()) {
    int windowWidth = window->getSize().x, windowHeight = window->getSize().y;

    const sf::Vector2f gameButtonSize = sf::Vector2f(400, 80);
    const sf::Vector2f statsButtonSize = sf::Vector2f(50, 50);
    const sf::Vector2f labelSize = sf::Vector2f(200, 60);
    const float textSize = 50;

    returnButton_ = std::make_shared<Button>(
            sf::Vector2f(windowWidth / 2, windowHeight * 9 / 10),
            gameButtonSize,
            "Return to menu",
            [this]() {
                close_ = true;
            });
    registerButton(returnButton_);

    initMaxSpeedControl(statsButtonSize, labelSize, textSize, windowWidth / 2, 100);
    initMaxEnginePowerControl(statsButtonSize, labelSize, textSize, windowWidth / 2, 200);
    initSteeringSpeedControl(statsButtonSize, labelSize, textSize, windowWidth / 2, 300);
    buttonManager_ = std::make_unique<ButtonManager>(buttons_);
}

int Workshop::Run() {
    close_ = false;
    while (!close_) {
        // EVENT handling
        sf::Event event;
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window_));
        while (window_->pollEvent(event)) {
            // "close_ requested" event: end while loop
            if (event.type == sf::Event::Closed) {
                window_->close();
                return 1;
            }
            // handle mouse click
            buttonManager_->ProcessEvent(event, mousePos);
        }
        buttonManager_->ManageClicks();
        buttonManager_->ManageHover(mousePos);
        // DRAWING
        window_->clear(sf::Color(60, 70, 80));
        for (auto &drawableObject : objects_) {
            drawableObject->Draw(window_);
        }
        window_->display();
    }
    buttonManager_->ReleaseButton();
    return 0;
}
