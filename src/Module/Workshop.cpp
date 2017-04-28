#include "Workshop.h"

Workshop::Workshop(sf::RenderWindow *window, RacePtr race) :
        Module(window),
        race_(race),
        carParams_(race_->GetVehicle()->GetCarParameters()) {
    int windowWidth = window->getSize().x, windowHeight = window->getSize().y;

    const sf::Vector2f gameButtonSize = sf::Vector2f(400, 80);
    const sf::Vector2f labelSize = sf::Vector2f(200, 60);
    const float textSize = 50;

    InitializeReturnButton(gameButtonSize, windowWidth, windowHeight);
    InitializeMaxSpeedControl(labelSize, textSize, windowWidth / 2, 100);
    InitializeMaxEnginePowerControl(labelSize, textSize, windowWidth / 2, 200);
    InitializeSteeringSpeedControl(labelSize, textSize, windowWidth / 2, 300);
    buttonManager_ = std::make_unique<ButtonManager>(buttons_);
}

int Workshop::Run() {
    close_ = false;
    bool interrupted = false;
    while (!close_) {
        interrupted = HandleEvents();

        Draw();
    }
    buttonManager_->ReleaseButton();
    return interrupted;
}

bool Workshop::HandleEvents() {
    sf::Event event;
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window_));
    while (window_->pollEvent(event)) {
        // "close_ requested" event: end while loop
        if (event.type == sf::Event::Closed) {
            window_->close();
            close_ = true;
            return true;
        }
        // handle mouse click
        buttonManager_->ProcessEvent(event, mousePos);
    }
    buttonManager_->ManageClicks();
    buttonManager_->ManageHover(mousePos);
    return false;
}

void Workshop::Draw() {
    // DRAWING
    window_->clear(sf::Color(60, 70, 80));
    for (auto &drawableObject : objects_) {
        drawableObject->Draw(window_);
    }
    window_->display();
}

void Workshop::InitializeMaxSpeedControl(const sf::Vector2f &labelSize, float textSize, int posX, int posY) {
    maxSpeedLabel_ = std::make_shared<Text>("Speed", "impact", sf::Vector2f(150, posY), textSize);
    objects_.push_back(maxSpeedLabel_);

    InitializeText(maxSpeedText_, std::to_string((int) carParams_->maxForwardSpeed), posX, posY, textSize);

    InitializeMinus(minusMaxSpeed_, posX, posY, carParams_->maxForwardSpeed, maxSpeedText_);
    InitializePlus(plusMaxSpeed_, posX, posY, carParams_->maxForwardSpeed, maxSpeedText_);
}

void Workshop::InitializeMaxEnginePowerControl(const sf::Vector2f &labelSize, float textSize, int posX, int posY) {
    maxEnginePowerLabel_ = std::make_shared<Text>("Acceleration", "impact", sf::Vector2f(150, posY), textSize);
    objects_.push_back(maxEnginePowerLabel_);

    InitializeText(maxEnginePowerText_, std::to_string((int) carParams_->maxEnginePower), posX, posY, textSize);

    InitializeMinus(minusMaxEnginePower_, posX, posY, carParams_->maxEnginePower,
                    maxEnginePowerText_);
    InitializePlus(plusMaxEnginePower_, posX, posY, carParams_->maxEnginePower,
                   maxEnginePowerText_);
}

void Workshop::InitializeSteeringSpeedControl(const sf::Vector2f &labelSize, float textSize, int posX, int posY) {
    steeringSpeedLabel_ = std::make_shared<Text>("Steering", "impact", sf::Vector2f(150, posY), textSize);
    objects_.push_back(steeringSpeedLabel_);

    InitializeText(steeringSpeedText_, std::to_string((int) carParams_->steeringSpeed), posX, posY, textSize);

    InitializeMinus(minusSteeringSpeed_, posX, posY, carParams_->steeringSpeed,
                    steeringSpeedText_);
    InitializePlus(plusSteeringSpeed_, posX, posY, carParams_->steeringSpeed,
                   steeringSpeedText_);
}

void Workshop::InitializeText(TextPtr &text, std::string initText, int posX, int posY, float textSize) {
    text = std::make_shared<Text>(
            initText, "impact",
            sf::Vector2f(posX, posY), textSize);
    objects_.push_back(text);
}

void Workshop::InitializeMinus(ButtonPtr &button, int posX, int posY, float &value, TextPtr &text) {
    InitializeDiff(button, posX - 150, posY, value, text, "-", -1);
}

void Workshop::InitializePlus(ButtonPtr &button, int posX, int posY, float &value, TextPtr &text) {
    InitializeDiff(button, posX + 150, posY, value, text, "+", 1);
}

void Workshop::InitializeDiff(ButtonPtr &button, int posX, int posY,
                              float &value, TextPtr &text, std::string label, int diff) {
    static const sf::Vector2f statsButtonSize = sf::Vector2f(50, 50);
    button = std::make_shared<Button>(sf::Vector2f(posX, posY), statsButtonSize, label,
                                      [this, &value, &text, diff]() {
                                          value += diff;
                                          text->SetText(std::to_string((int) value));
                                      });
    RegisterButton(button);
}

void Workshop::InitializeReturnButton(const sf::Vector2f &gameButtonSize, int windowWidth, int windowHeight) {
    returnButton_ = std::make_shared<Button>(
            sf::Vector2f(windowWidth / 2, windowHeight * 9 / 10),
            gameButtonSize,
            "Return to menu",
            [this]() {
                close_ = true;
            });
    RegisterButton(returnButton_);
}
