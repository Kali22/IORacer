#pragma once

#include <Activity.h>
#include <Event.h>
#include <Player.h>
#include <CarComponentManager.h>

class Workshop : public Activity {
public:
    Workshop(PlayerPtr player);

    void Init();

    void Run();

    void End();

    void EventAction(Event event);
private:
    void HandleKey(sf::Event::KeyEvent event);

    void SetTitleStyle(UITextBoxPtr textBox);

    void SetButtonStyle(UITextBoxPtr button);

    void SetSelectedButtonStyle(UITextBoxPtr button);

    void CreateRace(std::string name);

    void InitCategories();

    void UpdateCategoryUI();

    void UpdateComponentUI();

    void SelectComponent();

    ComponentCategoryPtr GetCurrentCategory() const;

    PlayerPtr player_;
    CarComponentManagerPtr carComponentManager_;

    std::vector<ComponentCategoryPtr> categories_;
    int categoryId_;

    UITextBoxPtr categoryBox_;
    UITextBoxPtr componentBox_;
    // TODO select already choosen object at startup
    // TODO change style of selected button
    // TODO print requriments
};

using WorkshopPtr = std::shared_ptr<Workshop>;

