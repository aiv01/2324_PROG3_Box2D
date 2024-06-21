#pragma once
#include "physics/Physics2DContactListener.h"

class Quad;

class BoxCollider2D
{
    public:
        BoxCollider2D(Quad* InQuad, CollisionCallBack CallBack = {});
    private:
        Quad* Object;
        class b2Body* Body;
        class b2Fixture* Fixture;
        CollisionCallBack UserData;

    friend class RigidBody2D;

};