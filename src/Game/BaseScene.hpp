#pragma once

class BaseScene {
public:
    virtual ~BaseScene() = 0;
    virtual void Update(double t, double dt) = 0;
    virtual void Draw() = 0;
    virtual void Init() = 0;
    virtual void DeInit() = 0;
private:

};
