#include "Workshop.h"

#include <ActivityManager.h>
#include <Gameplay.h>
#include <ViewportConst.h>

Workshop::Workshop(PlayerPtr player, CarComponentManagerPtr carComponentManager)
        : Activity("workshop"), player_(player),
          carComponentManager_(carComponentManager) {
}

void Workshop::Init() {
    UIBoxPtr back = userInterface_->CreateBox("background", centeredFullScreen);
    back->SetBackgroundTexture("menu_back");
    UITextBoxPtr title = userInterface_->CreateTextBox("title",
                                                       "Select component", 50,
                                                       sf::FloatRect(0.5, 0.075,
                                                                     1, 0.1));
    SetTitleStyle(title);

    categoryBox_ = userInterface_->CreateTextBox(
            "category", "Category", 30, sf::FloatRect(0.25, 0.5, 0.2, 0.05));
    componentBox_ = userInterface_->CreateTextBox(
            "component", "Component", 30, sf::FloatRect(0.75, 0.5, 0.2, 0.05));
    UITextBoxPtr categoryLeft = userInterface_->CreateTextBox(
            "category_left", "<", 30, sf::FloatRect(0.175, 0.65, 0.05, 0.05));
    UITextBoxPtr categoryRight = userInterface_->CreateTextBox(
            "category_right", ">", 30, sf::FloatRect(0.325, 0.65, 0.05, 0.05));
    UITextBoxPtr componentLeft = userInterface_->CreateTextBox(
            "component_left", "<", 30, sf::FloatRect(0.675, 0.65, 0.05, 0.05));
    UITextBoxPtr componentRight = userInterface_->CreateTextBox(
            "component_right", ">", 30, sf::FloatRect(0.825, 0.65, 0.05, 0.05));
    SetButtonStyle(categoryBox_);
    SetButtonStyle(componentBox_);
    SetButtonStyle(categoryRight);
    SetButtonStyle(categoryLeft);
    SetButtonStyle(componentRight);
    SetButtonStyle(componentLeft);
    InitCategories();
    UpdateCategoryUI();
}

void Workshop::Run() {
    RendererPtr renderer = activityManager_->GetRenderer();
    renderer->Clear();
    renderer->RenderUI(userInterface_);
    renderer->Display();
}

void Workshop::End() {
}

void Workshop::EventAction(Event event) {
    if (event.GetType() == SFML_EVENT) {
        sf::Event sfmlEvent = event.GetSFMLEvent();
        if (sfmlEvent.type == sf::Event::KeyPressed) {
            HandleKey(sfmlEvent.key);
        }
    } else if (event.GetType() == UI_EVENT) {
        if (event.GetUIEventType() == UI_EVENT_CLICK) {
            std::string uiElement = event.GetUIElement();
            if (uiElement == "quit_game") {
                activityManager_->RemoveActivity("player_selector");
                return;
            }
            if (uiElement == "component") {
                SelectComponent();
            } else if (uiElement == "category_right") {
                categoryId_ = (categoryId_ + 1) % categories_.size();
            } else if (uiElement == "category_left") {
                int size = categories_.size();
                categoryId_ = (categoryId_ + size - 1) % size;
            } else if (uiElement == "component_right") {
                GetCurrentCategory()->NextComponent();
            } else if (uiElement == "component_left") {
                GetCurrentCategory()->PreviousComponent();
            }
            UpdateCategoryUI();
        }
    }
}

void Workshop::HandleKey(sf::Event::KeyEvent event) {
    if (event.code == sf::Keyboard::Escape) {
        activityManager_->SetAsActive("player_selector");
    }
}

void Workshop::SetTitleStyle(UITextBoxPtr textBox) {
    textBox->SetTextColor(sf::Color::White);
    textBox->SetTextColorHover(sf::Color::White);
    textBox->SetBackgroundColor(sf::Color(0x2B405Bff));
    textBox->SetBackgroundColorHover(sf::Color(0x2B405Bff));
    textBox->SetOutlineColor(sf::Color(0xE1F0FFff));
    textBox->SetOutlineColorHover(sf::Color(0xE1F0FFff));
    textBox->SetOutlineThickness(1.f);
}

void Workshop::CreateRace(std::string name) {
    GameplayPtr race = std::make_shared<Gameplay>(name, 2);
    race->SetFirstPlayer("jacek");
    race->SetSecondPlayer("placek");
    activityManager_->AddActivity(race);
    activityManager_->SetAsActive("race");
}

void Workshop::SetButtonStyle(UITextBoxPtr button) {
    button->SetBackgroundColor(sf::Color(0x1c7396ff));
    button->SetBackgroundColorHover(sf::Color(0xD5E6E0ff));
    button->SetOutlineColor(sf::Color(0xE1F0FFff));
    button->SetOutlineColorHover(sf::Color(0x60758Cff));
    button->SetTextColor(sf::Color(0xD5E6E0ff));
    button->SetTextColorHover(sf::Color(0x1c7396ff));
    button->SetOutlineThickness(3.f);
}

void Workshop::InitCategories() {
    categories_ = carComponentManager_->GetComponentCategories();
    categoryId_ = 0; // TODO set for already choosen by player
}

void Workshop::UpdateCategoryUI() {
    categoryBox_->SetText(categories_[categoryId_]->GetName());
    UpdateComponentUI();
}


void Workshop::UpdateComponentUI() {
    componentBox_->SetText(categories_[categoryId_]->GetComponent()->GetName());
}

ComponentCategoryPtr Workshop::GetCurrentCategory() const {
    return categories_[categoryId_];
}

void Workshop::SelectComponent() {
    CarComponentPtr component = GetCurrentCategory()->GetComponent();
    if (component->IsTimesSufficient(player_->GetTimes())) {
        player_->GetCarConfiguration()->AddComponent(component);
    }
    // TODO change ui
}

void Workshop::SetSelectedButtonStyle(UITextBoxPtr button) {
    // TODO reformat - add colors to constants
    button->SetBackgroundColor(sf::Color(0xD5E6E0ff));
    button->SetBackgroundColorHover(sf::Color(0xD5E6E0ff));
    button->SetOutlineColor(sf::Color(0xE1F0FFff));
    button->SetOutlineColorHover(sf::Color(0x60758Cff));
    button->SetTextColor(sf::Color(0x1c7396ff));
    button->SetTextColorHover(sf::Color(0x1c7396ff));
    button->SetOutlineThickness(3.f);
}