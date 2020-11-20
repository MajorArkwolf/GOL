#pragma once
#include "Game/BaseScene.hpp"

class MainMenu : public BaseScene {
public:
    MainMenu();
    ~MainMenu() override;
    void Draw() override;
    void Update(double t, double dt) override;
    void Init() override;
    void DeInit() override;

};
