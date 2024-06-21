#pragma once

class Quad;

class BoxCollider2D
{
    public:
        BoxCollider2D(Quad* InQuad);
    private:
        Quad* Object;
        class b2Body* Body;
        class b2Fixture* Fixture;

    friend class RigidBody2D;
};