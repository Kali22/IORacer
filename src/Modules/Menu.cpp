#include "Menu.h"

Menu::Menu(RenderWindowPtr window, RacePtr race) :
        Module(window), race_(race), workshop_(std::make_shared<Workshop>(window_, race_)) {
    int windowWidth = window->getSize().x, windowHeight = window->getSize().y;
    sf::Vector2f menuButtonSize = sf::Vector2f(300, 80);

    InitializePlayButton(windowWidth, windowHeight, menuButtonSize);
    InitializeWorkshopButton(windowWidth, windowHeight, menuButtonSize);
    InitializeQuitButton(windowWidth, windowHeight, menuButtonSize);
}

void Menu::InitializePlayButton(int windowWidth, int windowHeight, const sf::Vector2f &menuButtonSize) {
    playButton_ = std::make_shared<Button>(
            sf::Vector2f(windowWidth / 2, windowHeight * 1 / 4),
            menuButtonSize,
            "Play",
            [this]() {
                if (race_->Run() != 0) {
                    close_ = true;
                };
                //race_->Reset(); TODO setup re initialization
            }
    );
    RegisterButton(playButton_);
}

void Menu::InitializeWorkshopButton(int windowWidth, int windowHeight, const sf::Vector2f &menuButtonSize) {
    workshopButton_ = std::make_shared<Button>(
            sf::Vector2f(windowWidth / 2, windowHeight * 2 / 4),
            menuButtonSize,
            "Workshop",
            [this]() {
                if (workshop_->Run() != 0) {
                    close_ = true;
                };
            }
    );
    RegisterButton(workshopButton_);
}

void Menu::InitializeQuitButton(int windowWidth, int windowHeight, const sf::Vector2f &menuButtonSize) {
    quitButton_ = std::make_shared<Button>(
            sf::Vector2f(windowWidth / 2, windowHeight * 3 / 4),
            menuButtonSize,
            "Quit",
            [this]() {
                close_ = true;
            }
    );
    RegisterButton(quitButton_);
}

int Menu::Run() {
    close_ = false;
    while (!close_) {
        bool mouseClick = false; // info for buttons

        HandleEvent(mouseClick);

        ServeButtons(mouseClick);

        Draw();
    }

    return 0;
}

void Menu::HandleEvent(bool &mouseClick) {
    sf::Event event;
    while (window_->pollEvent(event)) {
        // Modules closing event requested
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)) {
            close_ = true;
        }
        // handle mouse click
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            mouseClick = true;
        }
    }
}

void Menu::ServeButtons(bool mouseClick) {
    std::shared_ptr<Button> activeButton = nullptr;
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window_));
    // select Hovered button, change style
    for (auto &button : buttons_) {
        if (button->ToggleHover(mousePos)) {
            activeButton = button;
        }
    }
    if (activeButton != nullptr && mouseClick) {
        activeButton->OnClick();
    }
}

void Menu::Draw() {
    window_->clear(sf::Color(60, 70, 80));
    for (auto &drawableObject : objects_) {
        drawableObject->Draw(window_);
    }
    window_->display();
}
