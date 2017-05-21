#include "UI.h"

int UI::GetElementsCount() const {
    return (int) list_.size();
}

UI::UI(ActivityPtr activity) : activity_(activity) {

}

void UI::EventAction(sf::Event event) {
    for (auto item : list_)
        item.second->EventAction(event);
}

UIBoxPtr UI::CreateBox(std::string name, sf::FloatRect size) {
    UIBoxPtr box = std::make_shared<UIBox>(list_.size(), name, size, activity_);
    list_[name] = box;
    return box;
}

UIElementPtr UI::GetElementByName(const std::string &name) {
    UIElementPtr el  = list_[name];
    if (el == nullptr)
    {
        fprintf(stderr, "UI::GetElementByName: No such element like %s!\n", name.c_str());
        exit(1);
    }
    return el;
}

UITextBoxPtr UI::CreateTextBox(std::string name, std::string text, int fontSize, sf::FloatRect size) {
    UITextBoxPtr textbox = std::make_shared<UITextBox>(list_.size(), name, text, fontSize, size, activity_);
    list_[name] = textbox;
    return textbox;
}

void UI::DeleteElementByName(const std::string &name) {
    list_.erase(name);
}

std::map<std::string, UIElementPtr>::iterator UI::GetElements() {
    return list_.begin();
}
