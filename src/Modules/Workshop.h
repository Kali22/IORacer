#pragma once

#include <Activity.h>
#include <Event.h>
#include <Player.h>
#include <CarComponentManager.h>

class Workshop : public Activity {
public:
    Workshop();

    void Init();

    void Run();

    void End();

    void EventAction(Event event);
private:
    void HandleKey(sf::Event::KeyEvent event);

    void SetTitleStyle(UITextBoxPtr textBox);

    void SetButtonStyle(UITextBoxPtr button);

    void SetSelectedButtonStyle(UITextBoxPtr button);

    void InitCategories();

    void UpdateCategoryUI();

    void UpdateComponentUI();

    void SelectComponent();

    void UpdateComponentString(CarComponentPtr component) const;

    ComponentCategoryPtr GetCurrentCategory() const;

    PlayerPtr player_;
    CarConfigurationPtr configuration_;
    CarComponentManagerPtr carComponentManager_;

    std::vector<ComponentCategoryPtr> categories_;
    unsigned long categoryId_;

    UITextBoxPtr categoryBox_;
    UITextBoxPtr componentBox_;
};

using WorkshopPtr = std::shared_ptr<Workshop>;

