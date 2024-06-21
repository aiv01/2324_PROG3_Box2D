#pragma once
#include <box2d/box2d.h>
#include <functional>

struct CollisionCallBack
{
    std::function<void(class Quad*)>OnEnter = [](class Quad*){};

    class Quad* Object;
};

class Physics2DContactListener : public b2ContactListener
{
public:
    void BeginContact (b2Contact *contact) override;
    void EndContact (b2Contact *contact) override;
};