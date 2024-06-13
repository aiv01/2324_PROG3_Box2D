#pragma once
#include <glm/glm.hpp>
#include "Common.h"

class Quad 
{
public:
    Quad(int w, int h) 
    : Position(glm::vec3(0)), 
      Rotation(glm::vec3(0)), 
      Scale(glm::vec3(w, h, 0)),
      Color(Color_White)
    {};

    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;
    Color Color;
};