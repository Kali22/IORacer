#include <Workshop.h>
#include <UIColorConstants.h>
#include <ActivityManager.h>

Workshop::Workshop() : Activity("workshop") {}

void Workshop::Init() {
    player_ = activityManager_.lock()->GetPlayerManager()->GetActivePlayer();
    configuration_ = player_->GetCarConfiguration();
    carComponentManager_ = activityManager_.lock()->GetCarComponentManager();
    SetBackgroundToMenu();
    SetTitle("Select component");
    SetCategoryDisplay();
    SetComponentDisplay();

    InitCategories();
    UpdateCategoryUI();
}

void Workshop::SetCategoryDisplay() {
    categoryBox_ = userInterface_->CreateTextBox(
            "category", "Category", 30, sf::FloatRect(0.25, 0.5, 0.2, 0.05));
    UITextBoxPtr categoryLeft = userInterface_->CreateTextBox(
            "category_left", "<", 30, sf::FloatRect(0.175, 0.60, 0.05, 0.05));
    UITextBoxPtr categoryRight = userInterface_->CreateTextBox(
            "category_right", ">", 30, sf::FloatRect(0.325, 0.60, 0.05, 0.05));
    SetButtonStyle(categoryBox_);
    SetButtonStyle(categoryRight);
    SetButtonStyle(categoryLeft);
}

void Workshop::SetComponentDisplay() {
    componentBox_ = userInterface_->CreateTextBox(
            "component", "Component", 30, sf::FloatRect(0.75, 0.5, 0.2, 0.2));
    UITextBoxPtr componentLeft = userInterface_->CreateTextBox(
            "component_left", "<", 30, sf::FloatRect(0.675, 0.7, 0.05, 0.05));
    UITextBoxPtr componentRight = userInterface_->CreateTextBox(
            "component_right", ">", 30, sf::FloatRect(0.825, 0.7, 0.05, 0.05));
    SetButtonStyle(componentBox_);
    SetButtonStyle(componentRight);
    SetButtonStyle(componentLeft);
}

void Workshop::Run() {
    RendererPtr renderer = activityManager_.lock()->GetRenderer();
    renderer->Clear();
    renderer->RenderUI(userInterface_);
    renderer->Display();
}

void Workshop::End() {}

void Workshop::EventAction(Event event) {
    if (event.GetType() == SFML_EVENT) {
        sf::Event sfmlEvent = event.GetSFMLEvent();
        if (sfmlEvent.type == sf::Event::KeyPressed) {
            HandleKey(sfmlEvent.key);
        }
    } else if (event.GetType() == UI_EVENT && event.GetUIEventType() == UI_EVENT_CLICK) {
        HandleUIEventClick(event);
    }
}

void Workshop::HandleUIEventClick(Event event) {
    std::string uiElement = event.GetUIElement();
    unsigned long size = categories_.size();
    if (uiElement == "component") {
        SelectComponent();
    } else if (uiElement == "category_right") {
        categoryId_ = (categoryId_ + 1) % size;
    } else if (uiElement == "category_left") {
        categoryId_ = (categoryId_ + size - 1) % size;
    } else if (uiElement == "component_right") {
        GetCurrentCategory()->NextComponent();
    } else if (uiElement == "component_left") {
        GetCurrentCategory()->PreviousComponent();
    }
    UpdateCategoryUI();
}

void Workshop::HandleKey(sf::Event::KeyEvent event) {
    if (event.code == sf::Keyboard::Escape) {
        activityManager_.lock()->SetAsActive("main_menu");
    }
}

void Workshop::InitCategories() {
    categories_ = carComponentManager_->GetComponentCategories();
    categoryId_ = 0;
    for (auto category : categories_) {
        ModifierTypeE type = category->GetType();
        int id = configuration_->GetComponentId(type);
        if (id >= 0) {
            category->SetComponent((unsigned) id);
        }
    }
}

void Workshop::UpdateCategoryUI() {
    categoryBox_->SetText(GetCurrentCategory()->GetName());
    UpdateComponentUI();
}


void Workshop::UpdateComponentUI() {
    CarComponentPtr component = GetCurrentCategory()->GetComponent();
    UpdateComponentString(component);

    ModifierTypeE type = GetCurrentCategory()->GetType();
    int id = configuration_->GetComponentId(type);
    if (id == component->GetId()) {
        SetSelectedButtonStyle(componentBox_);
        return;
    }

    SetButtonStyle(componentBox_);
    if (!component->AreTimesSufficient(player_->GetTimes())) {
        componentBox_->SetBackgroundColor(sf::Color::Red);
        componentBox_->SetBackgroundColorHover(sf::Color::Red);
    }
}

void Workshop::UpdateComponentString(CarComponentPtr component) const {
    std::stringstream label;
    label << component->GetName().c_str();

    auto requirements = GetCurrentCategory()->GetComponent()->GetRequirement();
    if (requirements.empty()) {
        label << "\nNo requirements";
    } else {
        label << "\nRequirements:";
        for (auto it : requirements) {
            label << "\n" << it.first.c_str() << " - " << it.second << " s";
        }
    }
    componentBox_->SetText(label.str());
}

ComponentCategoryPtr Workshop::GetCurrentCategory() const {
    return categories_[categoryId_];
}

void Workshop::SelectComponent() {
    CarComponentPtr component = GetCurrentCategory()->GetComponent();
    if (!component->AreTimesSufficient(player_->GetTimes())) {
        return;
    }
    configuration_->AddComponent(component);
    SetSelectedButtonStyle(componentBox_);
}

void Workshop::SetSelectedButtonStyle(UITextBoxPtr button) {
    button->SetBackgroundColor(backgroundColorHover);
    button->SetBackgroundColorHover(backgroundColorHover);
    button->SetOutlineColor(outlineColorHover);
    button->SetOutlineColorHover(outlineColorHover);
    button->SetTextColor(textColorHover);
    button->SetTextColorHover(textColorHover);
    button->SetOutlineThickness(outlineThickness);
}
