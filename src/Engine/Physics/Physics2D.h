#pragma once

#include "box2d/box2d.h"

class Physics2D {
public:
    Physics2D() {};
    ~Physics2D() = default;

    void Init();

    void Step();

    float GetTimeStep() const { return timeStep; }
    void SetTimeStep(float value) { timeStep = value; }

    int GetSubStepCount() const { return subStepCount; }
    void SetSubStepCount(int value) { subStepCount = value; }

    b2BodyId CreateBody(const b2BodyDef *bodyDef);

private:
    b2WorldDef worldDef;
    b2WorldId worldId{0};

private:
    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;
};
