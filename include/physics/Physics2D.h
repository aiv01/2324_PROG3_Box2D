#pragma once
#include <glm/glm.hpp>
#include <box2d/box2d.h>

class Physics2D
{
public:
    Physics2D(glm::vec2 InGravity, float InFixedDeltaTime);
    b2Body* CreateBody(const b2BodyDef* InDef);
    void Step();
private:
    b2World* World;
    float FixedDeltaTime;
};