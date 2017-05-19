#include "UI.h"

int UI::GetElementsCount() const {
    return (int) list_.size();
}

UI::UI(ActivityPtr activity) : activity_(activity) {

}

void UI::EventAction(sf::Event event) {
    for (auto item : list_)
        item->EventAction(event);
}

UIElementPtr UI::GetElementByIdx(int i) {
    return list_[i];
}

UIBoxPtr UI::CreateBox(std::string name, sf::FloatRect size) {
    UIBoxPtr box = std::make_shared<UIBox>(list_.size(), name, size, activity_);

    list_.push_back(box);
    return box;
}

UIElementPtr UI::GetElementByName(std::string name) {
    for (auto item : list_) {
        if (item->GetName() == name)
            return item;
    }

    fprintf(stderr, "UI::GetElementByName: No such element like %s!\n", name.c_str());
    exit(1);
}

UITextBoxPtr UI::CreateTextBox(std::string name, std::string text, int fontSize, sf::FloatRect size) {
    UITextBoxPtr textbox = std::make_shared<UITextBox>(list_.size(), name, text, fontSize, size, activity_);
    list_.push_back(textbox);
    return textbox;
}
