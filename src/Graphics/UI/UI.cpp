#include <UI.h>

int UI::GetElementsCount() const {
    return (int) list_.size();
}

UI::UI(ActivityPtr activity) : activity_(activity) {}

void UI::EventAction(sf::Event event) {
    for (auto item : list_) {
        item.second->EventAction(event);
    }
}

UIBoxPtr UI::CreateBox(std::string name, sf::FloatRect size) {
    UIBoxPtr box = std::make_shared<UIBox>(list_.size(), name, size, activity_);
    list_[name] = box;
    return box;
}

UIMinimapPtr UI::CreateMinimap(std::string name, sf::FloatRect size,
                               RealVec mapSize, TexturePtr texture) {
    UIMinimapPtr minimap = std::make_shared<UIMinimap>(list_.size(), name,
                                                       size, activity_,
                                                       mapSize, texture);
    list_[name] = minimap;
    return minimap;
}

UIElementPtr UI::GetElementByName(const std::string &name) {
    auto el = list_.find(name);
    if (el == list_.end()) {
        std::cerr << "UI::GetElementByName: No such element like "
                  << name.c_str() << std::endl;
        exit(1);
    }
    return el->second;
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
