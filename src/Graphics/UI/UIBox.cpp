#include <UIBox.h>
#include <Texture/Texture.h>
#include <Activity.h>

UIBox::UIBox(int id, std::string name, ActivityPtr activity) : UIElement(id, name, activity) {

}

UIBox::UIBox(int id, std::string name, sf::FloatRect size, ActivityPtr activity) : UIElement(id, name, size, activity) {

}

