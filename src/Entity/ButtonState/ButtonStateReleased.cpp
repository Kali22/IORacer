//
// Created by pawel on 12.04.17.
//

#include <ButtonStateReleased.h>

ButtonStateType ButtonStateReleased::GetType() const {
    return RELEASED;
}

ButtonStatePtr ButtonStateReleased::ManageClicks(){
    return shared_from_this();
}

