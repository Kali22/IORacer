#include <UIBox.h>
#include <Texture.h>
#include <Activity.h>

UIBox::UIBox(int id, std::string name, WeakActivityPtr activity)
        : UIElement(id, name, activity) {
}

UIBox::UIBox(int id, std::string name, sf::FloatRect size, WeakActivityPtr activity)
        : UIElement(id, name, size, activity) {
}
