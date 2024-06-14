#include "physics/Physics2D.h"

Physics2D::Physics2D(glm::vec2 InGravity, float InFixedDeltaTime)
{
    b2Vec2 BoxGravity{InGravity.x, InGravity.y};
    World = new b2World(BoxGravity);
    FixedDeltaTime = InFixedDeltaTime;
}

b2Body* Physics2D::CreateBody(const b2BodyDef* InDef)
{
    return World->CreateBody(InDef);
}

void Physics2D::Step()
{
    World->Step(FixedDeltaTime, 8, 3);
}