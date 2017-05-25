#pragma once

#include <Activity.h>
#include <Event.h>
#include <Player.h>
#include <CarComponentManager.h>

class Workshop : public Activity {
public:
    Workshop(PlayerPtr player, CarComponentManagerPtr carComponentManager);

    void Init();

    void Run();

    void End();

    void EventAction(Event event);
private:
    void HandleKey(sf::Event::KeyEvent event);

    void SetTitleStyle(UITextBoxPtr textBox);

    void SetButtonStyle(UITextBoxPtr button);

    void CreateRace(std::string name);

    void InitCategories();

    void UpdateCategoryUI();

    void UpdateComponentUI();

    ComponentCategoryPtr GetCurrentCategory() const;

    PlayerPtr player_;
    CarComponentManagerPtr carComponentManager_;

    std::vector<ComponentCategoryPtr> categories_;
    int categoryId_;

    UITextBoxPtr categoryBox_;
    UITextBoxPtr componentBox_;
};

using WorkshopPtr = std::shared_ptr<Workshop>;

