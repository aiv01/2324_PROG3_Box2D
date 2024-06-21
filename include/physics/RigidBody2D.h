#pragma once

#include <box2d/box2d.h>
#include <glm/glm.hpp>

enum RigidBodyType
{
    Static = b2BodyType::b2_staticBody,
    Dynamic = b2BodyType::b2_dynamicBody,
    Kinematic = b2BodyType::b2_kinematicBody
};

class RigidBody2D
{
public:
    RigidBody2D(class Quad* InQuad, RigidBodyType Type);
    void AddForce(const glm::vec2& InForce);
    void AddImpulse(const glm::vec2& InImpulse);
    void SetVelocity(const glm::vec2& InVelocity);
    void Update();

private:
    class Quad* Object;
    class b2Body* Body;
    class b2Fixture* Fixture;

    friend class BoxCollider2D;
};