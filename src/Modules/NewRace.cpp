#include <NewRace.h>
#include <ActivityManager.h>
#include <Gameplay.h>

const int default_laps_number = 2;

NewRace::NewRace(RaceType type) : Activity("new_race"), type_(type), laps_(default_laps_number) {}

void NewRace::Init() {
    SetBackgroundToMenu();
    SetTitle("Setup your race");
    UITextBoxPtr m0 = userInterface_->CreateTextBox("map_0", "map_0", 30, sf::FloatRect(0.5, 0.5, 0.2, 0.05));
    UITextBoxPtr m1 = userInterface_->CreateTextBox("map_1", "map_1", 30, sf::FloatRect(0.5, 0.6, 0.2, 0.05));
    SetButtonStyle(m0);
    SetButtonStyle(m1);
    UITextBoxPtr laps = userInterface_->CreateTextBox("laps", std::to_string(laps_), 30,
                                                      sf::FloatRect(0.5, 0.2, 0.1, 0.05));
    SetButtonStyle(laps);
    UITextBoxPtr plus = userInterface_->CreateTextBox("inc_lap", "+", 30, sf::FloatRect(0.6, 0.2, 0.05, 0.05));
    SetButtonStyle(plus);
    UITextBoxPtr minus = userInterface_->CreateTextBox("dec_lap", "-", 30, sf::FloatRect(0.4, 0.2, 0.05, 0.05));
    SetButtonStyle(minus);
}

void NewRace::Run() {
    RendererPtr renderer = activityManager_.lock()->GetRenderer();
    Update();
    renderer->Clear();
    renderer->RenderUI(userInterface_);
    renderer->Display();
}

void NewRace::Update() {
    UITextBoxPtr nameTextBox = std::dynamic_pointer_cast<UITextBox>(userInterface_->GetElementByName("laps"));
    nameTextBox->SetText(std::to_string(laps_));
}

void NewRace::End() {}

void NewRace::EventAction(Event event) {
    if (event.GetType() == SFML_EVENT) {
        sf::Event sfmlEvent = event.GetSFMLEvent();
        if (sfmlEvent.type == sf::Event::KeyPressed) {
            HandleKey(sfmlEvent.key);
        }
    } else if (event.GetType() == UI_EVENT) {
        if (event.GetUIEventType() == UI_EVENT_CLICK) {
            if (event.GetUIElement() == "dec_lap")
                if (laps_ > 1) laps_--;
            if (event.GetUIElement() == "inc_lap")
                if (laps_ < 99) laps_++;
            if (event.GetUIElement() == "map_0")
                CreateRace("map_0");
            if (event.GetUIElement() == "map_1")
                CreateRace("map_1");
        }
    }
}

void NewRace::HandleKey(sf::Event::KeyEvent event) {
    if (event.code == sf::Keyboard::Escape) {
        if (type_ == SINGLE_PLAYER)
            activityManager_.lock()->SetAsActive("main_menu");
        else
            activityManager_.lock()->SetAsActive("player_selector");
    }
}

void NewRace::CreateRace(std::string name) {
    GameplayPtr race = std::make_shared<Gameplay>(name, laps_);
    PlayerPtr firstPlayer = activityManager_.lock()->GetPlayerManager()
            ->GetActivePlayer();
    race->SetFirstPlayer(firstPlayer);
    if (type_ == MULTI_PLAYER) {
        PlayerPtr secondPlayer = activityManager_.lock()->GetPlayerManager()
                ->GetSecondPlayer();
        race->SetSecondPlayer(secondPlayer);
    }
    activityManager_.lock()->AddActivity(race);
    activityManager_.lock()->SetAsActive("race");
}
