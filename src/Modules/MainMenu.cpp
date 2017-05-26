#include "MainMenu.h"
#include <ActivityManager.h>
#include <Workshop.h>
#include <CarComponentManager.h>
#include <ViewportConst.h>
#include <PlayerManager.h>

extern PlayerManagerPtr playerManager;

MainMenu::MainMenu() : Activity("main_menu") {

}

void MainMenu::Init() {
    UIBoxPtr back = userInterface_->CreateBox("background", centeredFullScreen);
    back->SetBackgroundTexture("menu_back");
    UITextBoxPtr play = userInterface_->CreateTextBox("start_game", "Play", 50, sf::FloatRect(0.5, 0.2, 0.2, 0.1));
    UITextBoxPtr workshop = userInterface_->CreateTextBox("workshop", "Workshop", 50, sf::FloatRect(0.5, 0.4, 0.2, 0.1));
    UITextBoxPtr quit = userInterface_->CreateTextBox("quit_game", "Quit",
                                                      50, sf::FloatRect(0.5, 0.6, 0.2, 0.1));
    SetButtonStyle(play);
    SetButtonStyle(workshop);
    SetButtonStyle(quit);
}

void MainMenu::Run() {
    RendererPtr renderer = activityManager_->GetRenderer();
    renderer->Clear();
    renderer->RenderUI(userInterface_);
    renderer->Display();
}

void MainMenu::End() {

}

void MainMenu::EventAction(Event event) {
    if (event.GetType() == SFML_EVENT) {
        if (event.GetSFMLEvent().type == sf::Event::KeyPressed) {
                HandleKey(event.GetSFMLEvent().key);
        }
    } else if (event.GetType() == UI_EVENT) {
        if(event.GetUIEventType() == UI_EVENT_CLICK) {
            if (event.GetUIElement() == "start_game")
                activityManager_->SetAsActive("new_race");
            if (event.GetUIElement() == "workshop") {
                // TODO Use stored player.
                CarComponentManagerPtr carComponentManager =
                        std::make_shared<CarComponentManager>();
                std::vector<CarComponentPtr> carComponents =
                        carComponentManager->GetBaseComponents();
                CarConfigurationPtr carConfiguration =
                        std::make_shared<CarConfiguration>(carComponents);

                //PlayerPtr player = std::make_shared<Player>("jacek", carConfiguration);
                WorkshopPtr workshop = std::make_shared<Workshop>(playerManager->GetActivePlayer(), carComponentManager);
                activityManager_->AddActivity(workshop);
                activityManager_->SetAsActive("workshop");
            }
            if (event.GetUIElement() == "quit_game")
                activityManager_->RemoveActivity("main_menu");
        }
    }
}

void MainMenu::HandleKey(sf::Event::KeyEvent event) {
    if(event.code == sf::Keyboard::Escape) {
        activityManager_->RemoveActivity("main_menu");
    }
}

void MainMenu::SetButtonStyle(UITextBoxPtr button) {
    button->SetBackgroundColor(sf::Color(0x1c7396ff));
    button->SetBackgroundColorHover(sf::Color(0xD5E6E0ff));
    button->SetOutlineColor(sf::Color(0xE1F0FFff));
    button->SetOutlineColorHover(sf::Color(0x60758Cff));
    button->SetTextColor(sf::Color(0xD5E6E0ff));
    button->SetTextColorHover(sf::Color(0x1c7396ff));
    button->SetOutlineThickness(3.f);
}
