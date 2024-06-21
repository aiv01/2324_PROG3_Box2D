#pragma once
#include <glm/glm.hpp>
#include "Common.h"
#include <string>

class Quad 
{
public:
    Quad(float w, float h) 
    : Position(glm::vec3(0)), 
      Rotation(glm::vec3(0)), 
      Scale(glm::vec3(w, h, 0)),
      Color(Color_White),
      RigidBody(nullptr),
      Collider(nullptr), 
      Name("Default Name")
    {};

    ~Quad()
    {
      if(RigidBody)
        delete RigidBody;
        
      if(Collider)
        delete Collider;
    }

    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;
    Color Color;
    class RigidBody2D* RigidBody;
    class BoxCollider2D* Collider;
    std::string Name;
};