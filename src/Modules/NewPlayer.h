#pragma once


#include <Activity.h>
#include <Event.h>

class NewPlayer : public Activity {
public:
    NewPlayer();

    void Init();

    void Run();

    void End();

    void EventAction(Event event);

private:

    void HandleKey(sf::Event::KeyEvent event);

    void SetButtonStyle(UITextBoxPtr button);

    void SetTextBoxStyle(UITextBoxPtr textBox);

    void Update();

    void CreatePlayer();

    std::string player_;

    const std::string resourcePath_ = "../players/";
};

using NewPlayerPtr = std::shared_ptr<NewPlayer>;
