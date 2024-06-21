#pragma once

#include <glm/glm.hpp>

class RigidBody2D
{
public:
    RigidBody2D(class Quad* InQuad);
    void AddForce(const glm::vec2& InForce);
    void AddImpulse(const glm::vec2& InImpulse);
    void Update();
private:
    class Quad* Object;
    class b2Body* Body;
    class b2Fixture* Fixture;

    friend class BoxCollider2D;
};