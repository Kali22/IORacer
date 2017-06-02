#include <Activity.h>
#include <UIColorConstants.h>

Activity::Activity(std::string name) : name_(name), state_(ACTIVITY_STATE_INIT), userInterface_(nullptr) {}

void Activity::Prepare(WeakActivityManagerPtr activityManager) {
    activityManager_ = activityManager;
    userInterface_ = std::make_shared<UI>(shared_from_this());
}

std::string Activity::GetName() const {
    return name_;
}

ActivityStateE Activity::GetState() const {
    return state_;
}

void Activity::SetReady() {
    state_ = ACTIVITY_STATE_RUN;
}

void Activity::SetBackgroundToMenu() {
    UIBoxPtr back = userInterface_->CreateBox("background", centeredFullScreen);
    back->SetBackgroundTexture("menu_back");
}

void Activity::SetTitle(std::string titleText) {
    UITextBoxPtr title = userInterface_->CreateTextBox(
            "title", titleText, 50, sf::FloatRect(0.5, 0.075, 1, 0.1));
    SetTitleStyle(title);
}

UIPtr Activity::GetUI() const {
    return userInterface_;
}

WeakActivityManagerPtr Activity::GetActivityManager() const {
    return activityManager_;
}

void Activity::SetTitleStyle(UITextBoxPtr textBox) {
    textBox->SetTextColor(sf::Color::White);
    textBox->SetTextColorHover(sf::Color::White);
    textBox->SetBackgroundColor(sf::Color(0x2B405Bff));
    textBox->SetBackgroundColorHover(sf::Color(0x2B405Bff));
    textBox->SetOutlineColor(outlineColor);
    textBox->SetOutlineColorHover(outlineColor);
    textBox->SetOutlineThickness(1.f);
}

void Activity::SetButtonStyle(UITextBoxPtr button) {
    button->SetBackgroundColor(backgroundColor);
    button->SetBackgroundColorHover(backgroundColorHover);
    button->SetOutlineColor(outlineColor);
    button->SetOutlineColorHover(outlineColorHover);
    button->SetTextColor(textColor);
    button->SetTextColorHover(textColorHover);
    button->SetOutlineThickness(outlineThickness);
}

void Activity::SetTextBoxStyle(UITextBoxPtr textBox) {
    textBox->SetBackgroundColor(backgroundColor);
    textBox->SetBackgroundColorHover(backgroundColor);
    textBox->SetOutlineColor(outlineColor);
    textBox->SetOutlineColorHover(outlineColor);
    textBox->SetTextColor(textColor);
    textBox->SetTextColorHover(textColor);
    textBox->SetOutlineThickness(outlineThickness);
}
