#pragma once 
#include "BaseScene.h"

class MainMenuScene : public BaseScene
{
public:
    CREATE_FUNC(MainMenuScene);
    virtual bool init() override;

private:
    void establishBackground();
    void createMenuButtons();
};